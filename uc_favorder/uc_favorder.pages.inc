<?php

/**
 * @file
 * This file contains the callbacks for the manu paths
 * Generates the page to show the favorite order to the user
 */

define('DELETE_BUTTON', t('Delete order'));
define('VIEW_BUTTON', t('View order'));
define('LOAD_BUTTON', t('Load order'));

/**
 * Page callback for favorite order autocomplete
 * Returns order names for the given user
 */
function uc_favorder_autocomplete($uid, $string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT name FROM {uc_favorder} WHERE LOWER(name) LIKE LOWER('%s%%') AND uid = '%d'", $string, $uid, 0, 10);
    while ($user = db_fetch_object($result)) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json($matches);
}

/**
 * Menu page callback.
 */
function uc_favorder_show_favorite_order($form_state, $uid = NULL) {
  $form = array();
  $default_id = FALSE;
  $result = db_query("SELECT order_id, name FROM {uc_favorder} WHERE uid = '%d'", $uid);
  while ($order = db_fetch_object($result)) {
    $default_id = $default_id ? $default_id : $order->order_id;
    $orders[$order->order_id] = $order->name;
  }
  $order_id = $form_state['storage']['order_id'] ? $form_state['storage']['order_id'] : $default_id;

  $products = uc_favorder_get_order($order_id);

  // Check if we have a stored favorite order
  if ($products) {

    // Load and theme the products of an order
    $content = '<div id="favorder" class="with-favorder">';

    $account = user_load($uid);
    // @todo Improve message
    $name = db_result(db_query("SELECT name FROM {uc_favorder} WHERE order_id = '%d'", $order_id));
    $content .=  '<p>' . t('Hello !user, this is the content of you favorite order %order.', array('!user' =>  $account->name, '%order' => $name)) . '</p>';

    // Counter
    $item_count = 0;
    // Order total
    $total = 0;
    // Prepare each product for display
    foreach ($products as $item) {
      $display_item = module_invoke($item->module, 'cart_display', $item);

      if (!empty($display_item)) {
        $items[] = array(
          'nid' => $display_item['nid']['#value'],
          'qty' => t('@qty&times;', array('@qty' => $display_item['qty']['#default_value'])),
          'title' => $display_item['title']['#value'],
          'price' => $display_item['#total'],
          'desc' => isset($display_item['description']['#value']) ? $display_item['description']['#value'] : FALSE,
        );
      }
      $item_count += $item->qty;
      $total += $display_item['#total'];
    }
    // Add a table of items in the order.
    $content .= theme('uc_cart_block_items', $items);

    // Build the item count text and cart links.
    $item_text = format_plural($item_count, '<span class="num-items">@count</span> Item', '<span class="num-items">@count</span> Items');
    $summary_links = NULL;

    $content .= theme('uc_cart_block_summary', $item_count, $item_text, $total, $summary_links);
    // Retrieve form to add products to the cart
    // Pass uid to the form
    $content .= '</div>';

    // Put the order as part of the form
    $form['order'] = array(
      '#value' => $content,
    );

    // Create the form the user interacts with
    $form['order_id'] = array(
      '#type' => 'select',
      '#title' => t("Favorite order"),
      '#options' => $orders,
      '#description' => t("Select an order."),
      '#default_value' => $order_id,
    );
    $form['view'] = array(
      '#type' => 'submit',
      '#value' => VIEW_BUTTON,
    );
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => DELETE_BUTTON,
    );
    $form['load'] = array(
      '#type' => 'submit',
      '#value' => LOAD_BUTTON,
      '#submit' => array('uc_favorder_load_favorder_submit'),
    );
    $form['clear'] = array(
      '#type' => 'checkbox',
      '#title' => t("Clear cart's content"),
      '#description' => t("Clear your cart's content before adding your favorite order."),
    );

  }
  // If no favorite order is stored, inform the user
  else{
    $content = '<div id="favorder" class="without-favorder">';
    $content .= t('Sorry, you have no favorite orders at this time.<br />To create one, start by adding products to your !cart.', array('!cart' => l('shopping cart', 'cart')));
    $content .= '</div>';
    $form['no_order'] = array(
      '#value' => $content,
    );
  }

  return $form;
}

/**
 * Form submit handler uc_favorder_show_favorite_order()
 */
function uc_favorder_show_favorite_order_submit($form, &$form_state) {
  switch ($form_state['values']['op']) {
    // If VIEW is pressed, save the order_id for the form rebuild
    case VIEW_BUTTON:
      $form_state['storage']['order_id'] = $form_state['values']['order_id'];
      break;
    // If DELETE is pressed, delete data form DB, and unset selected order.
    case  DELETE_BUTTON:
      unset($form_state['storage']['order_id']);
      drupal_set_message(t('Your favorite order %order has been deleted.', array('%order' => $form['order_id']['#options'][$form_state['values']['order_id']])), 'notice');
      _uc_favorder_delete($form_state['values']['order_id']);
      break;
  }
}