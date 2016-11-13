<?php
/**
 * @file
 * slider_paragraph.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function slider_paragraph_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_paragraphs_info().
 */
function slider_paragraph_paragraphs_info() {
  $items = array(
    'slide' => array(
      'name' => 'Slide',
      'bundle' => 'slide',
      'locked' => '1',
    ),
    'slider' => array(
      'name' => 'Slider',
      'bundle' => 'slider',
      'locked' => '1',
    ),
  );
  return $items;
}
