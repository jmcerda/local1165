<?php

/**
 * @file
 * Administrative functionality for auto assign role.
 */

/**
 * Provide a single block from the administration menu as a page.
 *
 * This function is often a destination for these blocks.
 * For example, 'admin/structure/types' needs to have a destination to be valid
 * in the Drupal menu system, but too much information there might be
 * hidden, so we supply the contents of the block.
 *
 * @return String
 *   The output HTML.
 */
function autoassignrole_admin_block_page() {
  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }
  return $output;
}

/**
 * Form builder; The settings form for automatic role assignment.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function autoassignrole_auto_settings() {
  $form['autoassignrole_auto_active'] = array(
    '#type' => 'radios',
    '#title' => t('Automatic role assignment'),
    '#default_value' => variable_get('autoassignrole_auto_active', 0),
    '#description' => t('Automatic role assignment occurs when the user first logins to the account. This happens without the users knowledge. Set to Enabled to allow this functionality or Disabled to not allow.'),
    '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  );

  $form['autoassignrole_admin_active'] = array(
    '#type' => 'radios',
    '#title' => t('Automatic role assignment for admin created accounts'),
    '#default_value' => variable_get('autoassignrole_admin_active', 0),
    '#description' => t('Automatic role assignment occurs when the user first logins to the account. This happens without the users knowledge. Set to Enabled to allow this functionality or Disabled to not allow.'),
    '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_auto_active"]' => array('value' => 1),
      ),
    ),
  );

  if ($roles = autoassignrole_get_roles()) {
    $form['autoassignrole_auto_roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Roles'),
      '#default_value' => variable_get('autoassignrole_auto_roles', array()),
      '#description' => t('Check the specific roles the user will automatically be assigned to when created by an administrator or through the new user registration process. The Authenticated User role is automatically assigned by Drupal core and can not be edited.'),
      '#options' => $roles,
      '#states' => array(
        'visible' => array(
          ':input[name="autoassignrole_auto_active"]' => array('value' => 1),
        ),
      ),
    );
  }

  return system_settings_form($form);
}

/**
 * Form builder; The settings form for user selectable role assignment.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function autoassignrole_user_settings() {
  $form['autoassignrole_user_active'] = array(
    '#type' => 'radios',
    '#title' => t('User role assignment'),
    '#default_value' => variable_get('autoassignrole_user_active', 0),
    '#description' => t('Toggles allowing end users to select roles when creating their accounts.'),
    '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  );

  if ($roles = autoassignrole_get_roles()) {
    $form['autoassignrole_user_roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Roles'),
      '#default_value' => variable_get('autoassignrole_user_roles', array()),
      '#description' => t('Check the specific roles the user will have the option of choosing. The Authenticated User role is automatically assigned by Drupal core and can not be edited.'),
      '#options' => $roles,
      '#states' => array(
        'visible' => array(
          ':input[name="autoassignrole_user_active"]' => array('value' => 1),
        ),
      ),
    );
  }

  $form['autoassignrole_user_multiple'] = array(
    '#type' => 'radios',
    '#title' => t('User role selection'),
    '#default_value' => variable_get('autoassignrole_user_multiple', 0),
    '#description' => t('Should the end user be allowed to choose a single role or can they choose multiple roles?'),
    '#options' => array(0 => t('Single role'), 1 => t('Multiple roles')),
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_user_active"]' => array('value' => 1),
      ),
    ),
  );

  $form['autoassignrole_user_selection'] = array(
    '#type' => 'radios',
    '#title' => t('Selection method'),
    '#default_value' => variable_get('autoassignrole_user_selection', AUTOASSIGNROLE_ELEMENT_RADIO_CHECKBOX),
    '#description' => t('The type of form elements the end user will be presented with.'),
    '#options' => array(
      AUTOASSIGNROLE_ELEMENT_RADIO_CHECKBOX => t('Radio Buttons/Checkboxes'),
      AUTOASSIGNROLE_ELEMENT_SELECT => t('Selection Box'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_user_active"]' => array('value' => 1),
      ),
    ),
  );

  $form['autoassignrole_user_required'] = array(
    '#type' => 'radios',
    '#title' => t('Required'),
    '#default_value' => variable_get('autoassignrole_user_required', 0),
    '#description' => t('Should the end user be required to choose a role?'),
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_user_active"]' => array('value' => 1),
      ),
    ),
  );

  $form['autoassignrole_user_sort'] = array(
    '#type' => 'radios',
    '#title' => t('Sorting'),
    '#default_value' => variable_get('autoassignrole_user_sort', 'SORT_ASC'),
    '#description' => t('Default sort order of roles the user will see.'),
    '#options' => array(
      'SORT_ASC' => t('Ascending'),
      'SORT_DESC' => t('Descending'),
      'SORT_WEIGHT' => t('Weight of field'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_user_active"]' => array('value' => 1),
      ),
    ),
  );

  // Set the user description filter format.
  $autoassignrole_user_description = _autoassignrole_get_user_description();

  $form['autoassignrole_user_description'] = array(
    '#type' => 'text_format',
    '#title' => t('User Role Description'),
    '#description' => t('The description displayed to the end user when they are selecting their role during registration.'),
    '#default_value' => $autoassignrole_user_description['value'],
    '#required' => FALSE,
    '#format' => $autoassignrole_user_description['format'],
    '#prefix' => '<div id="autoassignrole_user_description_wrapper">',
    '#suffix' => '</div>',
  );

  $form['autoassignrole_user_fieldset_title'] = array(
    '#type' => 'textfield',
    '#title' => t('User Role Fieldset Title'),
    '#description' => t('The title of the fieldset that contains role options.'),
    '#default_value' => variable_get('autoassignrole_user_fieldset_title', t('User Roles')),
    '#size' => 60,
    '#maxlength' => 128,
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_user_active"]' => array('value' => 1),
      ),
    ),
  );

  $form['autoassignrole_user_title'] = array(
    '#type' => 'textfield',
    '#title' => t('User Role Title'),
    '#description' => t('The title of the field that contains the role options the end user sees during registration.'),
    '#default_value' => variable_get('autoassignrole_user_title', t('Role')),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="autoassignrole_user_active"]' => array('value' => 1),
      ),
    ),
  );

  return system_settings_form($form);
}

/**
 * Provides a FAPI form for adding and editing pages.
 *
 * @param array $form
 *   The form API form array.
 * @param array $form_state
 *   The form API form state array.
 * @param stdClass|null
 *   The existing page object or NULL for a new page.
 *
 * @return array
 *   A form API renderable array.
 */
function autoassignrole_page_form($form, &$form_state, stdClass $page = NULL) {
  $is_new = empty($page);
  if ($is_new) {
    $page = autoassignrole_page_create();
  }

  $form['is_new'] = array(
    '#type' => 'value',
    '#value' => $is_new,
  );
  $form['export_type'] = array(
    '#type' => 'value',
    '#value' => $page->export_type,
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Page Title'),
    '#description' => t('Enter the title of the page'),
    '#size' => 60,
    '#required' => TRUE,
    '#default_value' => $page->title,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $page->name,
    '#disabled' => !$is_new,
    '#machine_name' => array(
      'exists' => 'autoassignrole_page_load',
      'source' => array('title'),
    ),
    '#required' => TRUE,
  );
  $form['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Role'),
    '#description' => t('Select the roles this page will assign'),
    '#options' => autoassignrole_get_roles(),
    '#required' => TRUE,
    '#default_value' => $page->roles,
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Page Path'),
    '#description' => t('Enter the Drupal path for the registration page for this role. This is a relative path based on your Drupal installation.'),
    '#size' => 60,
    '#required' => TRUE,
    '#default_value' => $page->path,
  );
  $form['menu'] = array(
    '#type' => 'select',
    '#title' => t('Menu'),
    '#description' => t('Which parent menu item should these pages appear under? This will only apply if you choose the "Standard" display option below.'),
    '#options' => menu_get_menus(),
    '#default_value' => $page->menu,
  );
  $form['display'] = array(
    '#type' => 'select',
    '#title' => t('Display type'),
    '#description' => t('Choose the way you would like these pages to be displayed.<br /><em>Standard</em> is equivalent to the core Drupal log in/ registration form, with tabs along the top.<br /><em>Individual</em> is a separate page without tabs.'),
    '#options' => array(
      AUTOASSIGNROLE_PAGE_DISPLAY_STANDARD => t('Standard'),
      AUTOASSIGNROLE_PAGE_DISPLAY_INDIVIDUAL => t('Individual'),
    ),
    '#default_value' => $page->display,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $is_new ? t('Add') : t('Save'),
  );

  return $form;
}

/**
 * Implements hook_form_validate().
 *
 * Check path to see if page already exists.
 */
function autoassignrole_page_form_validate($form_id, &$form_state) {
  $path = $form_state['values']['path'];

  // @todo need to check if the path already exists.
  if ($path) {
    if (preg_match('/[^A-Za-z0-9\/_-]+/', $path) || strpos(trim($path), '/') === 0) {
      form_set_error('path', '\'' . check_plain($path) . '\' ' . t('is not a valid path'));
    }
    else {
      $query = db_select('menu_links', 'm')
        ->fields('m', array('mlid'))
        ->condition('link_path', $path, 'like');
      $count = $query->countQuery()->execute()->fetchField();
      if (drupal_lookup_path('source', $path) || $count > 0) {
        // The menu item exists so need to check if the path has something other
        // than autoassign_role_path registered otherwise throw an error.
        $menu_item = menu_get_item($path);
        if (!isset($menu_item['page_callback']) && $menu_item['page_callback'] != 'autoassignrole_path') {
          form_set_error('path', '\'' . check_plain($path) . '\' ' . t('is already in use as a path'));
        }
      }
    }
  }
}

/**
 * Implements hook_form_submit().
 */
function autoassignrole_page_form_submit($form_id, &$form_state) {
  $values =& $form_state['values'];
  $is_new = $values['is_new'];

  $page = (object) array(
    'name' => $values['name'],
    'roles' => array_keys(array_filter($values['roles'])),
    'path' => $values['path'],
    'menu' => $values['menu'],
    'title' => $values['title'],
    'display' => $values['display'],
    'export_type' => $values['export_type']
  );

  ctools_include('export');
  $return = ctools_export_crud_save('autoassignrole_page', $page);

  if ($return !== FALSE) {
    menu_rebuild();
    if ($is_new) {
      drupal_set_message(t('Successfully created page @page.', array('@page' => $page->title)));
    }
    else {
      drupal_set_message(t('Successfully updated page @page.', array('@page' => $page->title)));
    }
    drupal_goto('admin/config/people/autoassignrole/pages');
  }
  else {
    drupal_set_message(t('Error when trying to save page.'), 'error');
  }
}

/**
 * Provides a FAPI form for deleting a pages.
 *
 * @param array $form
 *   The form API form array.
 * @param array $form_state
 *   The form API form state array.
 * @param stdClass|null
 *   The existing page object or NULL for a new page.
 * @param string $mode
 *   Mode: 'delete' or 'revert'.
 *
 * @return array
 *   A form API renderable array.
 */
function autoassignrole_page_delete_confirm($form, &$form_state, $page, $mode) {
  $form['page'] = array(
    '#type' => 'value',
    '#value' => $page,
  );
  if ($mode == 'delete') {
    $message = t('Are you sure you want to delete the page %name ?', array('%name' => $page->title));
    $button = t('Delete');
  }
  else {
    $message = t('Are you sure you want to revert the page %name ?', array('%name' => $page->title));
    $button = t('Revert');
  }

  return confirm_form($form, $message, 'admin/config/people/autoassignrole/pages', t('This action cannot be undone.'), $button);
}

/**
 * Form submit handler for autoassignrole_page_delete_confirm().
 */
function autoassignrole_page_delete_confirm_submit($form, &$form_state) {
  ctools_include('export');
  ctools_export_crud_delete('autoassignrole_page', $form_state['values']['page']);
  menu_rebuild();
  drupal_set_message(t('Successfully deleted page'));
  $form_state['redirect'] = 'admin/config/people/autoassignrole/pages';
}

/**
 * Function to display list of role-specific pages.
 *
 * @return array
 *   Returns a build array.
 */
function autoassignrole_list_pages() {
  $header = array(t('Name'), t('Title'), t('Roles'), t('Path'), t('Storage'), t('Operations'));
  $storage = array(
    'Normal' => t('Database'),
    'Default' => t('Code'),
    'Overridden' => t('Code. Overridden in database'),
  );

  $rows = array();
  ctools_include('export');
  foreach (ctools_export_crud_load_all('autoassignrole_page') as $page) {
    $roles = implode(', ', $page->roles);
    $operations = array(
      array(
        'title' => t('Edit'),
        'href' => 'admin/config/people/autoassignrole/pages/edit/' . $page->name,
      )
    );
    if (empty($page->in_code_only) && $page->type == 'Normal') {
      $operations[] = array(
        'title' => t('Delete'),
        'href' => 'admin/config/people/autoassignrole/pages/delete/' . $page->name,
      );
    }
    if ($page->type == 'Overridden') {
      $operations[] = array(
        'title' => t('Revert'),
        'href' => 'admin/config/people/autoassignrole/pages/revert/' . $page->name,
      );
    }

    $rows[] = array(
      $page->name,
      $page->title,
      $roles,
      $page->path,
      $storage[$page->type],
      theme(count($operations) == 1 ? 'links' : 'links__ctools_dropbutton', array(
        'links' => $operations,
        'attributes' => array('class' => array('links', 'inline'))
      )),
    );
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'sticky' => TRUE,
    'empty' => t('No Auto Assign pages yet.'),
  ));
}
