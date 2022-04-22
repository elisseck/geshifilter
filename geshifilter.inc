<?php

/**
 * @file
 * General GeSHi filter helper functions.
 */

/**
 * List of available languages.
 *
 * @return an array mapping language code to array with the language path and full language name.
 */
function _geshifilter_get_available_languages() {
  // try to get it from cache (database actually)
  $available_languages = config_get('geshifilter.settings', 'geshifilter_available_languages_cache');
  if ($available_languages === NULL) {
    // not in cache: build the array of available_languages
    $geshi_library = libraries_load('geshi');
    $available_languages = array();
    if ($geshi_library['loaded']) {
      $dirs = array($geshi_library['library path'] . '/geshi', backdrop_get_path('module', 'geshifilter') . '/geshi-extra');
      foreach ($dirs as $dir) {
        foreach (file_scan_directory($dir, '/.[pP][hH][pP]$/i') as $filename => $fileinfo) {
          // short name
          $name = $fileinfo->name;
          // get full name
          $geshi = new GeSHi('', $name);
          $geshi->set_language_path($dir);
          $fullname = $geshi->get_language_name();
          unset($geshi);
          // store
          $available_languages[$name] = array('language_path' => $dir, 'fullname' => $fullname);
        }
      }
      ksort($available_languages);
      // save array to database
      config_set('geshifilter.settings', 'geshifilter_available_languages_cache', $available_languages);
    }
  }
  return $available_languages;
}

/**
 * List of enabled languages.
 * (with caching)
 * @return array with enabled languages mapping language code to full name.
 */
function _geshifilter_get_enabled_languages() {
  static $enabled_languages = NULL;
  if ($enabled_languages === NULL) {
    $enabled_languages = array();
    $languages = _geshifilter_get_available_languages();
    foreach ($languages as $language => $language_data) {      
      if (config_get('geshifilter.settings', 'geshifilter_language_enabled_' . $language)) {
        $enabled_languages[$language] = $language_data['fullname'];
      }
    }
  }
  return $enabled_languages;
}

/**
 * Helper function for gettings the tags.
 * (with caching)
 */
function _geshifilter_get_tags($format, $filter) {
  static $geshifilter_tags_cache = array();

  if (!isset($geshifilter_tags_cache[$filter->format])) {
    $generic_code_tags = _geshifilter_tag_split(geshifilter_tags($format));
    $language_tags = array();
    $tag_to_lang = array();
    $enabled_languages = _geshifilter_get_enabled_languages();

    foreach ($enabled_languages as $language => $fullname) {
      $lang_tags = _geshifilter_tag_split(geshifilter_language_tags($language, $format));

      foreach ($lang_tags as $lang_tag) {
        $language_tags[] = $lang_tag;
        $tag_to_lang[$lang_tag] = $language;
      }
    }
    $geshifilter_tags_cache[$filter->format] = array($generic_code_tags, $language_tags, $tag_to_lang);
  }
  
  return $geshifilter_tags_cache[$filter->format];
}

/**
 * Helper function for generating a GeSHi object.
 * @param $language the language to generate a GeSHi object for
 */
function _geshifilter_geshi_factory($source_code, $language) {
  $available_languages = _geshifilter_get_available_languages();
  $geshi = new GeSHi($source_code, $language);
  $geshi->set_language_path($available_languages[$language]['language_path']);
  return $geshi;
}

/**
 * Helper function for splitting a string on white spaces.
 * Using explode(' ', $string) is not enough because it returns empty elements
 * if $string contains consecutive spaces.
 */
function _geshifilter_whitespace_explode($string) {
  return preg_split('/\s+/', $string, -1, PREG_SPLIT_NO_EMPTY);
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function _geshifilter_tag_split($string) {
  return preg_split('/\s+|<|>|\[|\]/', $string, -1, PREG_SPLIT_NO_EMPTY);
}

// General settings
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function geshifilter_use_format_specific_options() {
  return config_get('geshifilter.settings', 'geshifilter_format_specific_options');
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function geshifilter_tags($format = NULL) {
  $config = config('geshifilter.settings');
  if (!geshifilter_use_format_specific_options() || $format === NULL) {
    return $config->get('geshifilter_tags');
  }
  return $format->settings['geshifilter_tags'];
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function geshifilter_decode_entities($format = NULL) {
  $config = config('geshifilter.settings');
  if (!geshifilter_use_format_specific_options() || $format === NULL) {
    return $config->get('geshifilter_decode_entities');
  }
  return $format->settings['geshifilter_decode_entities'];
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function _geshifilter_tag_styles($format = NULL) {
  $config = config('geshifilter.settings');
  if (!geshifilter_use_format_specific_options() || $format === NULL) {
    return $config->get('geshifilter_tag_styles');
  }
  return $format->settings['geshifilter_tag_styles'];
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function geshifilter_language_tags($language, $format = NULL) {
  $config = config('geshifilter.settings');
  if (!geshifilter_use_format_specific_options() || $format === NULL) {
    return $config->get("geshifilter_language_tags_{$language}");
  }

  // @todo This is broken! The language tags are not being returned. It is because $filter is the string name and not the object being passed in.
  // Perhaps the $filter does not have settings but rather $format does.
  // $filter->settings is empty.
//  dpm($format->settings, 'format settings 179');
//  dpm($language, 'language');
//  dpm($format->settings["geshifilter_language_tags_{$language}"], 'line 183',);

  return $format->settings["geshifilter_language_tags_{$language}"];
}
