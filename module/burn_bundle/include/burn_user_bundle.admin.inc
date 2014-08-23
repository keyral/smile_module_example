<?php

/**
 * Add function burn_user_bundle_admin
 * @param null $action
 * @param null $bundle
 *
 * return to render view
 */
function burn_user_bundle_admin($action = NULL, $bundle = NULL){
    $render = array();
    $AllBundle = BurnBundleQuery::QueryAll();
    //var_dump($AllBundle); die('lol');
    if($action != '' && $bundle != ''){

    }
    else {
        $render[] = drupal_get_form('burn_user_bundle_add_form');
    }


    return $render;
}

/**
 * Add function burn_user_bundle_title
 * @param null $action
 * @param null $bundle
 * @return null|string
 *
 * return title for items
 */
function burn_user_bundle_title($action =  NULL, $bundle= NULL){
    if($action != '' && $bundle != ''){
        $entity = 'bob';
        return t("@action to @name", array('@action' => $action ,'@name' => $bundle));
    }
    else {
        return t('Config to burn bundle');
    }
}

/**
 * Add function burn_user_bundle_add_form
 * @param $form
 * @param $form_state
 * @param $bundle
 *
 * Return form by form api
 */
function burn_user_bundle_add_form($form,$form_state,$bundle = NULL){
    $form = array();
    $form['bundleid'] = array(
        '#type' => 'hidden',
        '#value' => isset($bundle->id) ? $bundle->id->value() : '',
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name to bundle'),
        '#default_value' => isset($bundle->name) ? $bundle->name->value() : '',
        '#size' => 60,
        '#maxlength' => 128,
        '#required' => TRUE,
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => isset($bundle->name) ? t('Modifier') : t('Created'),
    );
    return $form;
}
function burn_user_bundle_add_form_submit($form,&$form_state){
    $values = $form_state['values'];
    if($values['bundleid'] != ''){
        $bundle = BurnBundleQuery::Load($values['bundleid']);
    }
    else {
        $bundle = BurnBundleQuery::Create();
    }
    $bundle->name = $values['name'];
    BurnBundleQuery::Save($bundle);
}