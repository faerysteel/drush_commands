<?php

/**
 * @file
 * Drush Custom commands.
 */

/**
 * Implements hook_drush_command().
 */
function drush_commands_drush_command() {
  $commands['solr-server-change'] = array(
    'aliases' => array('ssc'),
    'description' => 'Change the solr server connection details',
    'options' => array(
      'scheme' => 'The http protocol for the solr host. If left blank the existing config protocol will be used.',
      'http_user' => 'The http auth user for the solr server.  If left blank the existing config user will be used.',
      'http_pass' => 'The http auth password for the solr server.  If left blank the existing config password will be used.',
      'host' => 'The host for the solr server.  If left blank the existing config host will be used.',
      'port' => 'The port of the solr server.  If left blank. the existing config port will be used.',
      'path' => 'The path to the solr core.  If left blank, the existing config core will be used.',
    ),
  );

  return $commands;
}

/**
 * Drush command logic - drush_[COMMAND_NAME]().
 */
function drush_drush_commands_solr_server_change() {
  // Get options.
  $scheme = drush_get_option('scheme');
  $http_user = drush_get_option('http_user');
  $http_pass = drush_get_option('http_pass');
  $host = drush_get_option('host');
  $port = drush_get_option('port');
  $path = drush_get_option('path');

  // If all options are NULL, return with an error. There is nothing to change.
  if (is_null($scheme)
    && is_null($http_user)
    && is_null($http_pass)
    && is_null($host)
    && is_null($port)
    && is_null($path)) {
    return drush_set_error('solr_server_change', 'No options set.  Nothing to change.');
  }

  // Load existing server.
  $sapi_server = search_api_server_load('solr');
  if (!$sapi_server) {
    // Exit with an error.
    return drush_set_error('solr_server_change', 'No solr config found.');
  }

  $options = $sapi_server->options;

  // Set server parts.
  if (!is_null($scheme)) {
    $options['scheme'] = $scheme;
  }
  if (!is_null($http_user)) {
    $options['http_user'] = $http_user;
  }
  if (!is_null($http_pass)) {
    $options['http_pass'] = $http_pass;
  }
  if (!is_null($host)) {
    $options['host'] = $host;
  }
  if (!is_null($port)) {
    $options['port'] = $port;
  }
  if (!is_null($path)) {
    $options['path'] = $path;
  }

  // Save the server.
  $sapi_server->update(array('options' => $options));
}
