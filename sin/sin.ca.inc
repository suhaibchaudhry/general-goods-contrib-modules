<?php
// $Id: sin.ca.inc,v 1.8 2010/09/02 16:05:55 thierrygd Exp $

/**
 * @file
 * CCK Field for Canadian Social Insurance Numbers.
 */
 
/** 
 * Verification for Canadian Social Insurance Numbers.  
 *
 * @param string $text
 * @return boolean Returns boolean FALSE if the Social Insurance Numbers is not valid. 
 * On success, returns a string containting the Social Insurance Numbers with some formatting.
 */
function valid_ca_sin($sinstring) {

  $sinstring = trim($sinstring);

  if (!is_numeric($sinstring) || strlen($sinstring) != 9) {
    return FALSE;
  }
  
  // for algorythm explanation see http://research.cs.queensu.ca/~bradbury/checkdigit/sincheck.htm
  $nos = str_split($sinstring);
  $validator = $nos[8];
  unset($nos[8]);
  $even_total = $odd_total = 0;
  
  foreach($nos as $key => $no) {
    // 'even' keys
    if ($key % 2 == 0) {
      $even_total += $no;
    }
    // 'odd' keys
    else {
      $no = $no * 2;
      if (strlen($no) > 1) {
        $split = str_split($no);
        $no = $split[0] + $split[1];
      }
      $odd_total += $no;
    }
  }
  
  $total = $even_total + $odd_total;
  
  if (10 - $total % 10 != $validator) {
    return FALSE;
  }
  return TRUE;
} 

/**
 * Formatting for Social Insurance Numbers.  
 *
 * @param string $sinstring
 * @return string Returns a string containting the Social Insurance Number with some formatting.
 */
function format_ca_sin($sinstring, $field) {

  $sinstring = trim($sinstring);
  //do some formatting 
  return $sinstring;
}