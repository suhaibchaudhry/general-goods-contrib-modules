Repeat customers are your best customers; you can rely on them to keep coming
back to your store so long as you provide the goods or services they need.  They
are a steady revenue stream, an easy sell.  But to quickly close the sale you
need to make it easier for them to find and purchase more of the same stuff
they've ordered previously.

This module lets your customer (or you, the admin) duplicate a previously
placed order.  It works by modifying the user order history page
(e.g. user/4/orders) to display a "Re-Order" button for each previous order.
The user can click on the link to have all the items from that previous order
added to his or her current cart.  Items added to the cart in this manner
will have the current price, but will otherwise preserve all the same
attributes as in the previous order.

When stock tracking (using the Inventory API) is enabled, products are only
added to the current cart if they are in stock.


To Use:

Install uc_reorder module.  Enable it at admin/build/modules.


Implementation details:

The proper place to put these mods is in uc_order, but rather than hack core
I used the same trick as in my uc_tracking module.  Because of that, you can't
have uc_reorder and uc_tracking enabled at the same time.  The trick is to
override the user/#/orders menu, defined in uc_order_menu(), to call my
uc_reorder_order_history() function instead of the core uc_order_history()
function.

The code is commented throughout.  Comments and enhancements welcome.


Know Bugs:

Doesn't work quite right with Product Kits.  The kit will get added to the
cart,
so it seems to work, BUT many database errors will be printed.  Not sure
what's going on there...
