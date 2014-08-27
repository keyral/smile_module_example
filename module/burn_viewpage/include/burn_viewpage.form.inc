<?php

function burn_page_edit($form, &$form_state, $bid = NULL){
    $All_bundle = BurnBundleQuery::QueryAll();
    module_load_include('inc','burn','include/burn_user.admin');
    $form = drupal_get_form('burn_user_add',$All_bundle, $bid->bid);
    return $form;
}