<?php

/**
 * @file
 * Kleosis reports and queries page
 *
 * This is early code. todo: update this...
 *
 */

/**
 * Display a list of Reports and Queries in kleosis (callback function)
 *
 * @return
 *   List of Reports and Queries in Kleosis
 */

function kleosis_reports_and_queries_page($form, &$form_state) {

  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), 'kleosis');
  $breadcrumb[] = l(t('Reports and Queries'), 'kleosis/reports_and_queries');
  $breadcrumb[] = t('Reports');

  // Set Breadcrumbs
  drupal_set_breadcrumb($breadcrumb);

  drupal_set_title(t('Reports'));

  $today = new DateTime('now');
  $today_start = $today->format('Y-m-d 00:00:00');
  $today_end = $today->format('Y-m-d 23:11:59');

  $header = array(
    'report_name' => array('data' => t('Report Name')),
    'report_category' => array('data' => t('Report Category')),
    'report_description' => array('data' => t('Report Description')),
    'report_filters' => array('data' => t('Report Filters')),
  );

  $options = array();

    $options[1] = array(
      'report_name' => l(t('Daily Attendance List'), 'daily-attendance-list', array('query' => array('atnd_date[min]' => $today_start, 'atnd_date[max]' => $today_end, 'destination' => 'kleosis/reports_and_queries'))),
      'report_category' => t('Attendance'),
      'report_description' => t('List of students who are absent this day'),
      'report_filters' => t('Attendance Date Range'),
    );
    $options[2] = array(
      'report_name' => l(t('Students Class List'), 'students-class-list', array('query' => array('destination' => 'kleosis/reports_and_queries'))),
      'report_category' => t('Classes'),
      'report_description' => t('List of Classes each student is currently enrolled in'),
      'report_filters' => t('Student Name'),
    );
    $options[3] = array(
      'report_name' => t('Instructor-Classes List'),
      'report_name' => l(t('Instructor-Classes List'), 'instructor-classes', array('query' => array('destination' => 'kleosis/reports_and_queries'))),
      'report_category' => t('Classes'),
      'report_description' => t('List of Classes each instructor is currently teaching'),
      'report_filters' => t('Instructor Name') . ', ' . t('Date Range'),
    );
    $options[4] = array(
      'report_category' => t('...'),
      'report_name' => t('...'),
      'report_description' => t('...'),
      'report_filters' => t('...'),
    );
    $options[5] = array(
      'report_category' => t('...'),
      'report_name' => t('...'),
      'report_description' => t('...'),
      'report_filters' => t('...'),
    );

  $form['reports'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $options,
        '#empty' => t('No reports are available.'),
      );
  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

/**
 * Display a list of User-created Reports
 *
 * @return
 *   List of User-created Reports
 */

function kleosis_user_reports_page($form, &$form_state) {

  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), 'kleosis');
  $breadcrumb[] = l(t('Reports and Queries'), 'kleosis/reports_and_queries');
  $breadcrumb[] = t('User-created Reports');

  // Set Breadcrumbs
  drupal_set_breadcrumb($breadcrumb);

  drupal_set_title(t('User-created Reports'));

  $today = new DateTime('now');
  $today_start = $today->format('Y-m-d 00:00:00');
  $today_end = $today->format('Y-m-d 23:11:59');

  $header = array(
    'report_name' => array('data' => t('Report Name')),
    'report_category' => array('data' => t('Report Category')),
    'report_description' => array('data' => t('Report Description')),
    'report_filters' => array('data' => t('Report Filters')),
  );

  $options = array();

    $options[1] = array(
//      'report_name' => l(t('Students per Gradelevel'), 'students_per_gradelevel', array('query' => array('destination' => 'kleosis/reports_and_queries'))),
      'report_name' => t('Students per Gradelevel'),
      'report_category' => t('Students'),
      'report_description' => t('List of students in each gradelevel'),
      'report_filters' => t('Gradelevel'),
    );
    $options[2] = array(
      'report_category' => t('...'),
      'report_name' => t('...'),
      'report_description' => t('...'),
      'report_filters' => t('...'),
    );
    $options[3] = array(
      'report_category' => t('...'),
      'report_name' => t('...'),
      'report_description' => t('...'),
      'report_filters' => t('...'),
    );
    $options[4] = array(
      'report_category' => t('...'),
      'report_name' => t('...'),
      'report_description' => t('...'),
      'report_filters' => t('...'),
    );

  $form['reports'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $options,
        '#empty' => t('No reports are available.'),
      );
  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

/*************************************************************************************************/

/**
 * Render a filtered list of courses in the database
 *
 * Legacy report. This code was based on the courses being defined in
 * a Kleosis custom table.  Course is now a Module using the Course content node
 *.The code is currently left here for historical purposes...
 *
 */
function kleosis_queries_courses_list_form() {

  $form['filter'] = courses_filter_form();
  $form['#submit'][] = 'courses_filter_form_submit';
  $form['list'] = kleosis_queries_courses_list();

  return $form;
}

/**
 * List of course filters that can be applied.
 */
function course_filters() {

  $filters['course_status'] = array(
    'title' => t('status'),
    'type' => 'select',
    'options' => array(
      '[any]' => t('any'),
      '1' => t('active'),
      '0' => t('not active'),
    ),
    '#prefix' => '<div style="float: left;width:300px" >',
    '#suffix' => '.&nbsp;&nbsp;&nbsp;.</div>',
  );

  $filters['length'] = array(
    'title' => t('length'),
    'type' => 'select',
    'options' => array(
      '[any]' => t('any'),
      '40' => '40',
      '60' => '60',
      '80' => '80',
    ),
    '#prefix' => '<div>   ',
    '#suffix' => '</div>',
  );
  $filters['program'] = array(
    'title' => t('program'),
    'type' => 'select',
    'options' => array(
      '[any]' => t('any'),
      't-prep' => 'T-Prep',
      'other' => 'Other',
    ),
    '#prefix' => '<div style="float: left;width:300px" >',
    '#suffix' => '</div>',
  );
  return $filters;
}

/**
 * Return form for course filters.
 */
function courses_filter_form() {
  $session = isset($_SESSION['course_filter']) ? $_SESSION['course_filter'] : array();
  $filters = course_filters();
  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only courses where'),
    '#theme' => 'exposed_filters__user',
    '#attributes' => array('class' => array('container-inline')),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  foreach ($session as $filter) {
    list($type, $value) = $filter;
      $value = $filters[$type]['options'][$value];
    $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
    if ($i++) {
      $form['filters']['current'][] = array('#markup' => t('and where %property is %value', $t_args));
    }
    else {
      $form['filters']['current'][] = array('#markup' => t('%property is %value', $t_args));
    }
  }

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
//    '#prefix' => ($i ? '<div class="additional-filters">' . t('and where ') . '&nbsp;&nbsp;&nbsp;</div>' : ''),
    '#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '&nbsp;&nbsp;&nbsp;</div>' : ''),
  );
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );
  foreach ($filters as $key => $filter) {
    $form['filters']['status']['filters'][$key] = array(
      '#type' => 'select',
      '#options' => $filter['options'],
      '#title' => check_plain($filter['title']),
      '#default_value' => '[any]',
    );
  }

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => (count($session) ? t('Refine') : t('Filter')),
    '#prefix' => '<div>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',
    '#suffix' => '</div>',
  );
  if (count($session)) {
    $form['filters']['status']['actions']['undo'] = array(
      '#type' => 'submit',
      '#value' => t('Undo'),
    );
    $form['filters']['status']['actions']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
    );
  }

  drupal_add_library('system', 'drupal.form');

  return $form;
}

/**
 * Process result from course queries filter form.
 */
function courses_filter_form_submit($form, &$form_state) {

  $filters = course_filters();
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      // Apply every filter that has a choice selected other than 'any'.
      foreach ($filters as $filter => $options) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '[any]') {
          // Flatten the options array to accommodate hierarchical/nested options.
          $flat_options = form_options_flatten($filters[$filter]['options']);
          // Only accept valid selections offered on the dropdown, block bad input.
          if (isset($flat_options[$form_state['values'][$filter]])) {
            $_SESSION['course_filter'][] = array($filter, $form_state['values'][$filter]);
          }
        }
      }
      break;
    case t('Undo'):
      array_pop($_SESSION['course_filter']);
      break;
    case t('Reset'):
      $_SESSION['course_filter'] = array();
      break;
  }
}

/**
 * Render a filtered list of course entries in the database.
 *
 * @see db_select()
 *
 */
function kleosis_queries_courses_list() {

  drupal_set_title(t('Courses List'));
  drupal_set_message(t('*Note: this report has been temporarily replaced by the list shown from the Courses menu item'));

  $header = array(
    'kcrs_id' => array('data' => t('Course id'), 'field' => 'kscrs.kcrs_id'),
    'courseno' => array('data' => t('Course No'), 'field' => 'kscrs.courseno'),
    'coursename' => array('data' => t('Course Name'), 'field' => 'kscrs.coursename'),
    'program' => array('data' => t('Program'), 'field' => 'kscrs.program'),
    'course_status' => array('data' => t('Status'), 'field' => 'kscrs.course_status'),
    'length' => array('data' => t('Length'), 'field' => 'kscrs.length'),
    'description' => array('data' => t('Description'), 'field' => 'kscrs.description'),
    'operations' => array('data' => t('Ops')),
  );

  $query = db_select('ks_courses', 'kscrs');
  $query->addField('kscrs', 'kcrs_id');
  $query->addField('kscrs', 'courseno');
  $query->addField('kscrs', 'coursename');
  $query->addField('kscrs', 'program');
  $query->addField('kscrs', 'course_status');
  $query->addField('kscrs', 'length');
  $query->addField('kscrs', 'description');
  // Filter example.
  $query->condition('kscrs.course_status', 0, '<>');
  // Only get items 0-999, for scalability reasons.
  $query->range(0, 1000);

  $filters = course_filters();
  // Extend Query with filter conditions.
  foreach (isset($_SESSION['course_filter']) ? $_SESSION['course_filter'] : array() as $filter) {
    list($key, $value) = $filter;
    $query->condition($key, $value);
  }

  $count_query = clone $query;
  $count_query->addExpression('COUNT(kscrs.kcrs_id)');


  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query->orderByHeader($header)
        ->setCountQuery($count_query);

  $entries = $query->execute()->fetchAll(PDO::FETCH_ASSOC);

  $rows = array();
  if (!empty($entries)) {
    foreach ($entries as $entry) {
      // Sanitize the data before handing it off to the theme layer.
      $row = array_map('check_plain', $entry);;
      $rows[] = $row + array('ops' => 'edit');
//      $rows[] = $row + array('ops' => l(t('edit'), 'kleosis/users/edit', array('query' => array('id' => $row['kcrs_id']))));
    }
 }
 $options = array();
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other options'),
    '#attributes' => array('class' => array('container-inline')),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Set'),
  );

  $form['courses'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('No content available.'),
      );
  $form['pager'] = array('#markup' => theme('pager'));
  $output = $form  ;

  return $output;
}

/*******************************************************************************/

// The following are legacy stub functions and are not currently used

function kleosis_queries_classes_list_form() {

  drupal_set_title(t('Classes List'));
  drupal_set_message(t('*Note: this report has been replaced by the list shown from the Classes menu item'));
  $header = array(
    'class_id' => array('data' => t('Class id')),
    'course_id' => array('data' => t('Course id')),
    'section' => array('data' => t('Section')),
    'start_date' => t('Start Date'),
    'end_date' => t('End Date'),
    'course_status' => array('data' => t('Status')),
    'length' => array('data' => t('Length')),
    'remarks' => array('data' => t('Remarks'))
  );

  $form['classes'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => NULL,
        '#empty' => t('No content available.'),
      );
  $form['pager'] = array('#markup' => theme('pager'));
  $output = $form  ;
  return $output;
}

function kleosis_queries_students_list_form() {

  drupal_set_title(t('Students List'));
  drupal_set_message(t('*Note: this report has been replaced by the list shown from the Students menu item'));
  $header = array(
    'student_id' => array('data' => t('Student id')),
    'drupal_uid' => array('data' => t('Drupal uid')),
    'moodle_uid' => array('data' => t('Moodle uid')),
    'firstname' => array('data' => t('Firstname')),
    'lastname' => t('Lastname'),
    'length' => array('data' => t('Length')),
    'city' => array('data' => t('City')),
    'country' => t('Country'),
    'age' => t('Age'),
    'status' => array('data' => t('Status'))
  );

  $form['students'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => NULL,
        '#empty' => t('No content available.'),
      );
  $form['pager'] = array('#markup' => theme('pager'));
  $output = $form  ;
  return $output;
}

function kleosis_queries_instructors_list_form() {

  drupal_set_title(t('Faculty List'));
  drupal_set_message(t('*Note: this report will be replaced by the list shown from the Faculty menu item'));
  $header = array(
    'staff_id' => array('data' => t('Staff id')),
    'drupal_uid' => array('data' => t('Drupal uid')),
    'moodle_uid' => array('data' => t('Moodle uid')),
    'firstname' => array('data' => t('Firstname')),
    'lastname' => t('Lastname'),
    'length' => array('data' => t('Length')),
    'city' => array('data' => t('City')),
    'country' => t('Country'),
    'age' => t('Age'),
    'status' => array('data' => t('Status'))
  );

  $form['instructors'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => NULL,
        '#empty' => t('No content available.'),
      );
  $form['pager'] = array('#markup' => theme('pager'));
  $output = $form  ;
  return $output;
}

