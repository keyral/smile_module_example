<?php



function burn_user_admin($type = NULL)
{

    $content = array();
    if ($type) {
        $content[] = drupal_get_form('burn_user_add', $type);
        if($query = BurnQuery::QueryByType($type)){
            $results = BurnQuery::Load(array_keys($query));

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
    // On attache les formulaires des fields attachés
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
    // Enregistrement dans la base "books"
    drupal_write_record('burn_user', $user);
    // L'objet est construit avec les propriété issues de form_state
    entity_form_submit_build_entity('burn_user', $user, $form, $form_state);
    // Laissons aussi une chance a d'autres modules d'intervenir sur les Fields attachérs.
    field_attach_submit('burn_user', $user, $form, $form_state);
    // On insere les données des fields dans la base de données.
    field_attach_insert('burn_user', $user);
    // Et un petite message de confirmation.
    drupal_set_message(
        t('new @type got added' ,
            array('@type' => $user->type))
    );
}