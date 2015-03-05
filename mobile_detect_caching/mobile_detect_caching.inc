<?php

function mobile_detect_caching_alter_cid() {
  require_once DRUPAL_ROOT . '/sites/all/libraries/Mobile_Detect/Mobile_Detect.php';

  if (class_exists('Mobile_Detect')) {
    try {
      $detect = new Mobile_Detect();

      if ($detect->isMobile()) {
        $extra = 'mobile_detect_caching_mobile';
      }
      else {
        $extra = 'mobile_detect_caching_notmobile';
      }

      if ($detect->isTablet()) {
        $extra .= '&mobile_detect_caching_tablet';
      }
      else {
        $extra .= '&mobile_detect_caching_nottablet';
      }

      if (!empty($extra) && ($_SERVER['REQUEST_URI'])) {
        if (strpos($_SERVER['REQUEST_URI'], '?') === FALSE) {
          $_SERVER['REQUEST_URI'] .= '?' . $extra;
        }
        else {
          $_SERVER['REQUEST_URI'] .= '&' . $extra;
        }
      }
    } catch (Exception $e) {
      // nop
    }
  }
}

mobile_detect_caching_alter_cid();
