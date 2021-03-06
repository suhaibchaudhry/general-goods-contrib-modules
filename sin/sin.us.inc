<?php
// $Id: sin.us.inc,v 1.8 2010/09/02 16:05:55 thierrygd Exp $

/**
 * @file
 * CCK Field for American Social Insurance Numbers.
 */
 
/**
 * Verification for American Social Insurance Numbers.  
 *
 * @param string $text
 * @return boolean Returns boolean FALSE if the Social Insurance Numbers is not valid. 
 * On success, returns a string containting the Social Insurance Numbers with some formatting.
 */
function valid_us_sin($sinstring) {

  $sinstring = trim($sinstring);

  if (!preg_match("/^\d{3}\-?\d{2}\-?\d{4}$/i",$sinstring)) { 
  	return false; 
  }
  //999-99-9999 or 999999999
  else 
  {
	return true;
  }
} 

/**
 * Formatting for Social Insurance Numbers.  
 *
 * @param string $sinstring
 * @return string Returns a string containting the Social Insurance Number with some formatting.
 */
function format_us_sin($sinstring, $field) {

  $sinstring = trim($sinstring);
  //do some formatting 
  return $sinstring;
}
