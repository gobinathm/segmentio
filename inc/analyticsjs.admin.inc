<?php

/**
 * @file
 * Administrative page callbacks for the analyticsjs module.
 */

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function analyticsjs_admin_settings_form($form_state) {
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['account']['analyticsjs_write_key'] = array(
    '#title' => t('Write Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('analyticsjs_write_key', ''),
    '#size' => 15,
    '#maxlength' => 20,
    '#required' => TRUE,
    '#description' => t('This Write Key is unique to each Project you have configured in <a href="@segmentio">Segment.io</a>. To get a Write Key, <a href="@analyticsjs">register your Project with Segment.io</a>, or if you already have registered your site, go to your Segment.io Project Settings page.analyticsjs will use this write key to send data to your project.', array('@segmentio' => 'https://segment.io/login', '@analyticsjs' => 'https://segment.io/login')),
  );

  // Advanced Analytics.js configurations.
  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advance Configurations'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $page_tracking = variable_get('analyticsjs_visibility_pages', 0);
  $pages = variable_get('analyticsjs_pages', ANALYTICSJS_EXCLUSION_LIST);

  $form['advanced']['analyticsjs_visibility_pages'] = array(
      '#type' => 'radios',
      '#title' => t('Add tracking to specific pages'),
      '#options' => array(t('Every page except the listed pages'), t('The listed pages only'), ),
      '#default_value' => $page_tracking,
  );

  $form['advanced']['analyticsjs_pages'] = array(
      '#type' => 'textarea',
      '#title' => t('Pages'),
      '#title_display' => 'invisible',
      '#default_value' => $pages,
      '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
      '#rows' => 10,
    );

  // Privacy configurations.
  $form['advanced']['privacy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Universal web tracking opt-out'),
    '#description' => t('If enabled and your server receives the <a href="@donottrack">Do-Not-Track</a> header from the client browser, the Google Analytics module will not embed any tracking code into your site. Compliance with Do Not Track could be purely voluntary, enforced by industry self-regulation, or mandated by state or federal law. Please accept your visitors privacy. If they have opt-out from tracking and advertising, you should accept their personal decision. This feature is currently limited to logged in users and disabled page caching.', array('@donottrack' => 'http://donottrack.us/')),
    '#default_value' => variable_get('analyticsjs_privacy', 1),
  );

  return system_settings_form($form);
}