<?php
/**
 * @file
 * Panels render to display search results.
 */


$plugin = array(
  'title' => t('Ting simple search'),
  'description' => t("Search using simple search api"),
  'single' => TRUE,
  'render callback' => 'ting_simple_search_simple_search_result_content_type_render',
  'category' => t('Ting'),
  'render last' => FALSE,
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

/**
 * Render the custom content type.
 */
function ting_simple_search_simple_search_result_content_type_render($subtype, $conf, $panel_args, $context) {
  $keys = NULL;
  if (!empty($context) && isset($context->data)) {
    $keys = $context->data;
  }
  
  // Display nothing at all if no keywords were entered.
  if (empty($keys)) {
    if (!empty($conf['override_no_key'])) {
      $block = new stdClass();
      $block->title = $conf['no_key_title'];
      $block->content = check_markup($conf['no_key'], $conf['no_key_format'], FALSE);
      return $block;
    }
    return;
  }

  // Build the content type block.
  $block = new stdClass();
  $block->module = 'search';
  $block->delta = 'result';

  $results = ting_simple_search_search($keys);


  if (!empty($results)) {
    $block->title = t('Search results');
    $block->content = $results;
  }
  else {
    if (empty($conf['override_empty'])) {
      $block->title = t('Your search yielded no results');
      $block->content = $prefix . search_help('search#noresults', drupal_help_arg()) . $suffix;
    }
    else {
      $block->title = $conf['empty_title'];
      $block->content = check_markup($conf['empty'], $conf['empty_format'], FALSE);
    }
  }

  return $block;
}


