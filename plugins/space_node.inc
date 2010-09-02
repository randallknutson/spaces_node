<?php
// $Id$

/**
 * @file
 *
 * Include file for space_type
 *
 * This defines a node as a space.
 */

/**
 * node integration for Spaces.
 */
class space_node extends space_type {
  var $node = NULL;

  /**
   * Override of title().
   */
  function title() {
    return $this->node->title;
  }

  /**
    * Override of load().
    */
  function load() {
    // The 0 id means a new node is being saved. Instantiate a space
    // so preset values can become active.
    if ($this->id === 0) {
      return TRUE;
    }
    elseif ($this->node = node_load($this->id)) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Override access_admin().
   */
  function access_admin($account = NULL) {
    global $user;
    $account = isset($account) ? $account : $user;

    if ($this->node && (node_access("update", $this->node, $account))) {
      return TRUE;
    }
    elseif (user_access('administer spaces', $account)) {
      return TRUE;
    }
    return parent::access_admin($account);
  }
}
