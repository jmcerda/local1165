<?php
/**
 * @file
 * local_newswire_view.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function local_newswire_view_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_day';
  $strongarm->value = 'd';
  $export['date_format_day'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_month';
  $strongarm->value = 'M';
  $export['date_format_month'] = $strongarm;

  return $export;
}
