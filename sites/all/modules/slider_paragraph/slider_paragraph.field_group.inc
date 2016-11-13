<?php
/**
 * @file
 * slider_paragraph.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function slider_paragraph_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_slide_body|paragraphs_item|slide|default';
  $field_group->group_name = 'group_slide_body';
  $field_group->entity_type = 'paragraphs_item';
  $field_group->bundle = 'slide';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Slide Body',
    'weight' => '1',
    'children' => array(
      0 => 'field_slide_title',
      1 => 'field_slide_text',
      2 => 'field_slide_button',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'Slide Body',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'slide-body',
        'element' => 'div',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $field_groups['group_slide_body|paragraphs_item|slide|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Slide Body');

  return $field_groups;
}
