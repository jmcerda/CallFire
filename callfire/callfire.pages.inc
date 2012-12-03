<?php

/**
 * @file
 * CallFire remote notification functions.
 *
 * @creation November 2012
 * @author Rod Jackson (RDJ)
 */


/**
 * Initial entry point function for the module's CallFire notification URL
 */
function callfire_notification() {

	$post = file_get_contents("php://input");
	if ($post) {
		$xml = simplexml_load_string($post);
		// let each service scrutinize the XML to see if it is for them
		$results = module_invoke_all('callfire_notification', $xml);
	}

}


/**
 * Sends out an email alert from the CallFire module
 */
function callfire_mail($to, $txt, $priority = 3) {

	$success = false;
	
  //$to = variable_get('uc_bitpay_alert_email', '');
	
	if ($to != '') {
	  // prepare to construct the message array we need
		$m = array();
    // include the preface to the body of the email
  	$preface = t("ATTENTION: This is an alert from the CallFire module of your website.") . "\r\n\r\n";
    // establish the body of the email
		$m['body'] = $preface . $txt;
    // get the 'From' address
		$from = _get_bp_email_from_address();
	  // setup the other email elements
		$m['id'] = 'uc_bitpay_alert';
		$m['subject'] = t('CallFire Notification');
		$m['to'] = $to;
		$m['from'] = $from;
		// finalize the email headers
		$headers = array();
		$headers['To'] = $to;
		$headers['From'] = $from;
		$headers['Sender'] = $from;
		$headers['X-Priority'] = $priority;
		$m['headers'] = $headers;
  	// actually send the email
    $success = drupal_mail_send($m);
  }
	
	return $success;
}


/**
 * Returns the string of the 'From' email address to be used when
 * sending out email alerts from the module.
 */
function _get_cf_email_from_address() {

  //return uc_store_email_from();
}
