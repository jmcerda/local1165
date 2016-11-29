<?php


function fire_preprocess_page(&$variables) {

    $variables['site_phone'] = variable_get('custom_admin_phone', '000.000.000');
    $variables['site_email'] = variable_get('custom_admin_email', 'email not set');

    $variables['facebook_url'] = variable_get('custom_admin_facebook', 'link not set');
    $variables['twitter_url'] = variable_get('custom_admin_twitter', 'link not set');
    $variables['linkedin_url'] = variable_get('custom_admin_linkedin', 'link not set');
    $variables['instagram_url'] = variable_get('custom_admin_instagram', 'link not set');

    $variables['address'] = nl2br(variable_get('custom_admin_address', 'address not set'));

    $variables['slider'] = null;
    $variables['left_side_image']= null;

    if ($node = menu_get_object()) {
        $variables['slider'] = field_view_field('node', $node, 'field_page_slider', array('label' => 'hidden'));
        $variables['left_side_image']= field_view_field('node', $node, 'field_left_side_image', array('label' => 'hidden'));
    }

    $menu_tree = menu_tree_all_data('main-menu');
    $variables['main_menu'] = menu_tree_output($menu_tree);
}


/**
 * Create the calendar date box.
 */
function fire_preprocess_calendar_datebox(&$vars) {
  if ($vars['view']->name == 'shifts_calendar' && !empty($vars['selected'])) {
    foreach ($vars['items'] as $item) {
      $item = reset($item);
      if (isset($item[0]->calendar_start)) {
        $time = strtotime($item[0]->calendar_start);
        if (date('Y-m-d', $time) == $vars['date']) {
          $color = $item[0]->rendered_fields['field_color'];
        }
      }
    }
  }
  $date = $vars['date'];
  $view = $vars['view'];
  $vars['day'] = intval(substr($date, 8, 2));
  $force_view_url = !empty($view->date_info->block) ? TRUE : FALSE;
  $month_path = calendar_granularity_path($view, 'month');
  $year_path = calendar_granularity_path($view, 'year');
  $day_path = calendar_granularity_path($view, 'day');
  $vars['url'] = str_replace(array($month_path, $year_path), $day_path, date_pager_url($view, NULL, $date, $force_view_url));
  $link_attributes = array();
  if (!empty($color)) {
    $link_attributes['background-color'] = $color;
  }
  $vars['link'] = !empty($day_path) ? l($vars['day'], $vars['url'], array('attributes' => $link_attributes)) : $vars['day'];
  $vars['granularity'] = $view->date_info->granularity;
  $vars['mini'] = !empty($view->date_info->mini);
  if ($vars['mini']) {
    if (!empty($vars['selected'])) {
      $vars['class'] = 'mini-day-on';
    }
    else {
      $vars['class'] = 'mini-day-off';
    }
  }
  else {
    $vars['class'] = 'day';
  }
}

/*
 * Implements template_preprocess_view().
 */
function fire_preprocess_views_view(&$vars) {
  // if a single event in the day in the day view - go to that event
  if (($vars['name'] == 'shifts_calendar' || $vars['name'] == 'event_calendar') && $vars['display_id'] == 'page_3') {
    if (count($vars['view']->result) == 1) {
      if (!empty($vars['view']->result[0]->nid)) {
        drupal_goto('node/' . $vars['view']->result[0]->nid);
      }
    }
  }
}
