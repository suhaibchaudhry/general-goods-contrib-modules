<?php
// $Id: sin.fr.inc,v 1.8 2010/09/02 16:05:55 thierrygd Exp $

/**
 * @file
 * CCK Field for French Social Insurance Numbers.
 */
  
/**
 * Verification for French Social Insurance Numbers.  
 *
 * @param string $text
 * @return boolean Returns boolean FALSE if the Social Insurance Numbers is not valid. 
 * On success, returns a string containting the Social Insurance Numbers with some formatting.
 */
function valid_fr_sin($sinnumber) {

  $sinnumber = trim($sinnumber);

  if (!preg_match("/^(1|2)[ ]{0,1}\d{2}[ ]{0,1}\d{2}[ ]{0,1}\d{2}[ ]\d{3}[ ]{0,1}\d{3}[ ]{0,1}\d{2}$/i",$sinnumber)) { 
  	return false; 
  }
  //1 72 06 28 151 045 34 
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
function format_fr_sin($sinnumber, $field) {

  $sinnumber = trim($sinnumber);
  //do some formatting 
  return $sinnumber;
}
