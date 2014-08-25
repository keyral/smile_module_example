<?php


function burn_user_admin($user_id = NULL)
{
    //Query All type
    if (module_exists('burn_bundle')) {
        $burn_bundle_type = BurnBundleQuery::QueryAll();
    } else {
        $burn_bundle_type = FALSE;
    }
    $content = array();
    if ($user_id) {

        $content[] = ($burn_bundle_type) ? drupal_get_form('burn_user_add', $burn_bundle_type, $user_id) : array();
        if ($query = BurnQueryUser::QueryByType($user_id)) {
            $results = BurnQueryUser::Load(array_keys($query));
            $rows = array();
            foreach ($results as $result) {
                $rows[] = array(l($result->bid, 'burn/user/' . $result->type . '/' . $result->bid), $result->name, $result->type);
            }
            $header = array(t('ID'), t('Name'), t('Type'));
            $content[] = array(
                '#theme' => 'table',
                '#header' => $header,
                '#rows' => $rows,
            );
        }
    } else {
        $content[] = ($burn_bundle_type) ? drupal_get_form('burn_user_add', $burn_bundle_type) : array();
        $rows = array();
        $rows[] = array(l(t('Contrib'), 'admin/burn/contrib'));
        $rows[] = array(l(t('Admin'), 'admin/burn/admin'));
        $rows[] = array(l(t('Visitor'), 'admin/burn/visitor'));
        $header = array('Type');
        $content[] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
        );
    }
    return $content;
}

function burn_user_add($form, &$form_state, $types, $user_id = NULL)
{
    if (isset($user_id) && $user_id != NULL) {
        $user = new BurnWrapperUser($user_id);
    } else {
        $user = new stdClass();
    }
    $form['user'] = array(
        '#type' => 'value',
        '#title' => 'config name to burn user',
        '#value' => $user,
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => 'Name to user',
        '#default_value' => (isset($user->name)) ? $user->name : '',
        '#required' => TRUE,
    );
    if ($user_id == NULL) {
        $bundle = array();
        foreach ($types as $type) {
            $bundle += array($type->name => $type->name);
        }
        $form['type'] = array(
            '#type' => 'radios',
            '#title' => t('Type to bundle'),
            '#options' => $bundle,
        );
    } else {
        $form['type'] = array(
            '#type' => 'item',
            '#title' => 'bundle user', // . $user_id->type,
        );
        field_attach_form('burn_user', $user, $form, $form_state);
    }


    $form['actions'] = array('#type' => 'actions');
    $form['actions']['add'] = array(
        '#type' => 'submit',
        '#value' => 'add'
    );
    return $form;
}

function burn_user_add_validate($form, &$form_state)
{
    entity_form_field_validate('burn_user', $form, $form_state);
}

function burn_user_add_submit($form, &$form_state)
{
    try {
        if (empty($form_state['values']['user'])) {
            throw new Exception("User is not define !");
        }
        $user = $form_state['values']['user'];
        $user->name = $form_state['values']['name'];
        $user->type = $form_state['values']['type'];
        //drupal_write_record('burn_user', $user);
        $entity = entity_create('burn_user', (array)$user);
        // construct to entity
        entity_form_submit_build_entity('burn_user', $entity, $form, $form_state);
        // Call to hook for field used in entity.
        field_attach_submit('burn_user', $entity, $form, $form_state);
        // insert to information in bd
        BurnQueryUser::Save($entity);
        //no use field_attache to no call controller custom
        //field_attach_insert('burn_user', $user);

        drupal_set_message(
            t('New user @name : @type to add !!!! ',
                array('@name' => $user->name, '@type' => $user->type))
        );

    } catch (Exception $e) {
        drupal_set_message(t('Burn add user failed. Message = %message',
            array('%message' => $e->getMessage())), 'error');
        watchdog('error', t('Burn add user failed. Message = %message, query= %query',
            array('%message' => $e->getMessage())));
    }



}
