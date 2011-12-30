<?php
// $Id$

/**
 * @file
 *  Helper functions used throughout the module
 */

/**
 * Helper function to insert a lunchnlearn record
 *
 * @param $title
 *  The title of the lunchnlearn record
 * @param $status
 *  The status of the lunchnlearn record
 * @param $uid
 *  The uid of the lunchnlearn record
 *
 * @return $record
 *  The newly inserted recorded if saved, false otherwise
 */
function lunchnlearn_helpers_insert_lunchnlearn_record($title, $status, $uid) {
	$record = new stdClass;
  
  // Instantiate the object
  $record->title = $title;
  $record->status = $status;
  $record->uid = $uid;
  
  /**
   * Run our presave hook before the node is saved. Because the
   * record object is passed by reference, it allows other modules to modify the
   * object prior to being saved. We invoke functions directly to allow
   * passing the record object by reference.
   */
  foreach (module_implements('lunchnlearnrecordapi') as $name) {
    $function = $name .'_lunchnlearnrecordapi';
    $function($record, 'presave');
  }
  
  $is_saved = drupal_write_record('lunchnlearn', $record);
  
  if ($is_saved == SAVED_NEW) {
    /**
     * Call our insert hook. This will not invoke the function directly
     * since module_invoke_all will invoke call_user_func_array
     */
    module_invoke_all('lunchnlearnrecordapi', $record, 'insert');
    return $record;
  }
  return FALSE;
}

/**
 * A contrived function to build an array
 */
function lunchnlearn_helpers_build_contrived_array() {
	$array = range(0, 10);
	drupal_alter('lunchnlearn_contrived_array', $array);
  return $array;
}

/**
 * Removes all the records from the record array
 */
function lunchnlearn_helpers_delete_all_records() {
	$sql =<<<SQL
    DELETE FROM {lunchnlearn}
SQL;
  db_query($sql);
}


