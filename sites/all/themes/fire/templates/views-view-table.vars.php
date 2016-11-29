<?php
/**
 * @file
 * Stub file for "views_view_table" theme hook [pre]process functions.
 */

/**
 * Pre-processes variables for the "views_view_table" theme hook.
 *
 * See template for list of available variables.
 *
 * @see views-view-table.tpl.php
 *
 * @ingroup theme_preprocess
 */
function fire_preprocess_views_view_table(&$variables) {
  fire_include('bootstrap', 'templates/system/table.vars.php');
  _fire_table_add_classes($variables['classes_array'], $variables);
}
