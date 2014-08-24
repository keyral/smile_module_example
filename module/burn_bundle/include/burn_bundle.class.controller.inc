<?php

class BurnBundleQuery
{
    public static function QueryAll()
    {
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user_bundle');
        $result = $query->execute();
        return isset($result['burn_user_bundle']) ? entity_load('burn_user_bundle', array_keys($result['burn_user_bundle'])) : FALSE;
    }

    public static function Load($bid)
    {
        $entity = entity_load('burn_user_bundle', (array)$bid);
        return array_pop($entity);
    }

    public static function Create()
    {
        return entity_create('burn_user_bundle', array());
    }

    public static function Save($bundle)
    {
        return entity_save('burn_user_bundle', $bundle);

    }

    public static function Delete($bid)
    {
        try {
            if (entity_delete('burn_user_bundle', $bid)) {
                drupal_set_message(t('Bundle deleted'),'status');
            }
        } catch (Exception $e) {
            drupal_set_message(t('Entity Delete failed. Message = %message, query= %query',
                array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
            watchdog('error', t('Entity Delete failed. Message = %message, query= %query',
                array('%message' => $e->getMessage(), '%query' => $e->query_string)), array(), WATCHDOG_ERROR, NULL);
        }
        drupal_goto('admin/burn/bundle');
    }
}