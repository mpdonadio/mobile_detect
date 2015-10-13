<?php

/**
 * @file
 * Cache backend include for the mobile_detect_caching module.
 */

/**
 * Add to settings.php:
 * $conf['cache_backends'][] = 'sites/all/modules/mobile_detect/mobile_detect_caching/mobile_detect_caching.inc';
 * $conf['cache_class_cache_page'] = 'MobileDetectCache';
 * $conf['mobile_detect_library'] = 'sites/all/libraries/Mobile_Detect/Mobile_Detect.php';
 */

include_once DRUPAL_ROOT . '/' . variable_get('mobile_detect_library', 'sites/all/libraries/Mobile_Detect/Mobile_Detect.php');


/**
 * Defines a Mobile Detect cache implementation.
 */
class MobileDetectCache extends DrupalDatabaseCache implements DrupalCacheInterface {

  /**
   * Replace DrupalDatabaseCache::set().
   */
  function set($cid, $data, $expire = CACHE_PERMANENT) {
    $cid = $this->mobile_detect_caching_alter_cid() . $cid;
    parent::set($cid, $data, $expire);
  }

  /**
   * Replace DrupalDatabaseCache::getMultiple().
   */
  function getMultiple(&$cids) {
    if (is_array($cids)) {
      foreach ($cids as $key => $cid) {
        $cids[$key] = $this->mobile_detect_caching_alter_cid() . $cid;
      }
    }
    return parent::getMultiple($cids);
  }

  /**
   * Change $cid depending from the mobile detect results.
   */
  protected function mobile_detect_caching_alter_cid() {
    $device = '';

    if (class_exists('Mobile_Detect')) {
      try {
        $detect = new Mobile_Detect();

        if ($detect->isMobile()) {
          $device = 'mobile:';
        }
        elseif ($detect->isTablet()) {
          $device = 'tablet:';
        }

      } catch (Exception $e) {
        // nop
      }
    }
    return $device;
  }
}
