<?php

/**
 * @file
 *    Drush integration for mobile_detect
 */

/**
 * Implements hook_drush_command
 * 
 * @see http://drupalcontrib.org/api/drupal/contributions!drush!docs!drush.api.php/function/hook_drush_command/7
 * 
 * @return array An array containing your commands and their callbacks
 */
function mobile_detect_drush_command() {
  $commands = array();
  
  $commands['md-getlibrary'] = array(
    'callback' => 'mobile_detect_get_library',
    'description' => dt('Downloads the Mobile Detect library from Github '),    
  );
  
  return $commands;
}

/**
 * Clone the Mobile Detect repository from Github
 * 
 * @todo Pass another parameter allowing to choose source (clone/wget)
 */
function mobile_detect_get_library() {
    $path = 'sites/all/libraries/Mobile_Detect';

    //Create path if it doesn't exist
    if (!is_dir($path)) {
      drush_op('mkdir', $path);
      drush_log(dt('Directory @path was created', array ('@path' => $path)), 'notice');
    }
    
    drush_op('chdir', $path);
    
    if (drush_shell_exec("git clone git://github.com/serbanghita/Mobile-Detect.git .")) {
      drush_log(dt('Mobile Detect was downloaded successfully to @path', array ('@path' => $path)), 'success');
    }
    else {
      drush_log(dt('Drush could not download Mobile Detect to @path', array ('@path' => $path)), 'error');
    }
}