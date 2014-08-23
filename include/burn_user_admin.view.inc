<?php



function burn_user_admin($type = NULL)
{

    $content = array();
    if ($type) {
        $content[] = drupal_get_form('burn_user_add', $type);
        if($query = BurnQueryUser::QueryByType($type)){
            $results = BurnQueryUser::Load(array_keys($query));

        $rows = array();
         foreach($results as $result){
             $rows[] = array(l($result->bid,'burn/'.$result->bid), $result->name, $result->type);
         }
        $header = array(t('ID'), t('Name'), t('Type'));
        $content[] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
        );
        }
    } else {
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


function burn_user_add($form ,&$form_state, $type) {
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => 'name'
    );

    $user = new stdClass();
    $user->type = $type;
    $form['user'] = array(
        '#type' => 'value',
        '#value' => $user
    );
    $form['type'] = array(
        '#type' => 'value',
        '#value' => $type
    );
    // Attach field to form
    field_attach_form('burn_user',$user, $form, $form_state);

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['add'] = array(
        '#type' => 'submit',
        '#value' => 'add'
    );
    return $form;
}
function burn_user_add_validate($form, &$form_state) {
    entity_form_field_validate('burn_user', $form, $form_state);
}
function burn_user_add_submit($form, &$form_state) {
    $user = $form_state['values']['user'];
    $user->name = $form_state['values']['name'];
    //drupal_write_record('burn_user', $user);
    $entity = entity_create('burn_user', (array) $user);
    // construct to entity
    entity_form_submit_build_entity('burn_user', $entity, $form, $form_state);
    // Call to hook for field used in entity.
    field_attach_submit('burn_user', $entity, $form, $form_state);
    // insert to information in bd
    BurnQueryUser::Save($entity);
    //no use field_attache to no call controller custom
    //field_attach_insert('burn_user', $user);
    drupal_set_message(
        t('new @type got added' ,
            array('@type' => $user->type))
    );
}