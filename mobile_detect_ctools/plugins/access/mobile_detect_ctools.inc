<?php

$plugin = array(
  'title' => t('Mobile Detect: device type'),
  'description' => t('Control access by mobile device type.'),
  'callback' => 'mobile_detect_ctools_ctools_access_check',
  'default' => array('type' => 'view'),
  'settings form' => 'mobile_detect_ctools_ctools_access_settings',
  'settings form submit' => 'mobile_detect_ctools_ctools_access_settings_submit',
  'summary' => 'mobile_detect_ctools_ctools_access_summary',
  'required context' => array(
  ),
);

function mobile_detect_ctools_ctools_access_settings ($form, &$form_state, $conf)
{
  $form['settings']['type'] = array(
    '#title' => t('Mobile Device Type'),
    '#type' => 'radios',
    '#options' => array(
      'isMobile' => t('Mobile'),
      'isTablet' => t('Tablet'),
    ),
    '#description' => t('Mobile device type.'),
    '#default_value' => $conf['type'],
  );
  
  $detect = mobile_detect_get_object();
  
  foreach ($detect->getRules() as $name => $regex) {
    $form['settings']['type']['#options']['is' . $name] = $name;
  }
  
  return $form;
}

function mobile_detect_ctools_ctools_access_check ($conf, $context)
{
  $detect = mobile_detect_get_object();
	
  return $detect->{$conf['type']}();
}

function mobile_detect_ctools_ctools_access_summary ($conf, $context)
{
  return t('User is using a %type device.', array(
    '%type' => preg_replace('/^is/', '', $conf['type'])
  ));
}
