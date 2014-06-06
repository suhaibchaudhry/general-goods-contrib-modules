<?php
// $Id: sin.uk.inc,v 1.4 2010/09/02 16:05:55 thierrygd Exp $

/**
 * @file
 * CCK Field for British Social Insurance Numbers.  ==> to be done (just a copy of us one for now) 
 */
 
/**
 * Verification for British Social Insurance Numbers.  
 *
 * @param string $text
 * @return boolean Returns boolean FALSE if the Social Insurance Numbers is not valid. 
 * On success, returns a string containting the Social Insurance Numbers with some formatting.
 */
function valid_uk_sin($sinstring) {

  $sinstring = trim($sinstring);

  if (!preg_match("/^\d{3}\-?\d{2}\-?\d{4}$/i",$sinstring)) { 
  	return false; 
  }
  //999-99-9999 or999999999
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
function format_uk_sin($sinstring, $field) {

  $sinstring = trim($sinstring);
  //do some formatting 
  return $sinstring;
}
