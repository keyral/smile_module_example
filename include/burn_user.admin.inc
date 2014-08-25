<?php


function burn_user_admin($user_id = NULL)
{
    //Query All type
    if (module_exists('burn_bundle')) {
        $All_bundle = BurnBundleQuery::QueryAll();
    } else {
        $All_bundle = FALSE;
    }
    $content = array();
        $BurnQueryAllUser = BurnQueryUser::QueryAll();


        $content[] = ($All_bundle) ? drupal_get_form('burn_user_add', $All_bundle, $user_id) : array();
        if ($BurnQueryAllUser) {
            $BurnAllUser = BurnQueryUser::Load(array_keys($BurnQueryAllUser));
            $rows = array();
            foreach ($BurnAllUser as $result) {
                $rows[] = array(
                    l($result->bid, 'admin/burn/user/'. $result->bid),
                    $result->name, $result->type,
                    format_date($result->created),
                    format_date($result->changed),
                    l(t('edit'),'admin/burn/user/'.$result->bid). ' ' . l(t('delete'), 'admin/burn/delete_user/'.$result->bid),
                );
            }
            $header = array(t('ID'), t('Name'), t('Type'),t('created'), t('changed'),t('Operation'));
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
    if ($user_id != NULL) {
        $query_user = BurnQueryUser::Load(array($user_id));
        $user_load = array_pop($query_user);
        $user = new BurnWrapperUser($user_load);
    } else {
        $user_load = new stdClass();
    }
    $form['user'] = array(
        '#type' => 'value',
        '#title' => 'config name to burn user',
        '#value' => $user_load,
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => 'Name to user',
        '#default_value' => (isset($query_user)) ? $user->name->value() : '',
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
            '#type' => 'value',
            '#title' => 'bundle user : ' . $user_load->type,
            '#value' => $user_load->type,
        );
        field_attach_form('burn_user', $user_load, $form, $form_state);
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
        if(isset($user->bid)){
            $entity = entity_load('burn_user',array($form_state['values']['user']->bid));
            $entity = array_pop($entity);
        }
        else {
        $entity = entity_create('burn_user', (array)$user);
        }
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


/**
 * Add function callback to delete items.
 * @param $id
 */
function burn_user_admin_delete($bid = NULL){
if($bid != NULL){
    if(BurnQueryUser::Delete($bid)){
        drupal_set_message(t('Burn user is delete'), 'status');
        drupal_goto('admin/burn/user');
    }
    else {
        drupal_set_message(t('Burn user is not delete'), 'error');
    }

}
}