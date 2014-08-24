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
        switch ($action) {
            case "edit":
                $bundle = BurnBundleQuery::Load(array($bundle));
                $render[] = drupal_get_form('burn_user_bundle_add_form',$bundle);
                break;
            case "delete":
                BurnBundleQuery::Delete($bundle);
                break;
        }
    }
    else {
        $render[] = drupal_get_form('burn_user_bundle_add_form');
        $rows = array();
        $bundles = BurnBundleQuery::QueryAll();
        if(isset($bundles)){
            foreach($bundles as $bundle){
                $rows[] =array($bundle->name, l(t('Edit'),'admin/burn/bundle/edit/'.$bundle->bid),l(t('Delete'),'admin/burn/bundle/delete/'.$bundle->bid));
            }
        }
        $header = array(t('Name'), t('Edit'), t('Delete'));
        $render[] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
        );
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
        $entity = BurnBundleQuery::Load($bundle);
        return t("@action to @name", array('@action' => $action ,'@name' => $entity->name));
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
function burn_user_bundle_add_form($form, $form_state, $bundle = NULL){
    $form = array();
    $form['bundleid'] = array(
        '#type' => 'hidden',
        '#value' => isset($bundle->bid) ? $bundle->bid : '',
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name to bundle'),
        '#default_value' => isset($bundle->name) ? $bundle->name : '',
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
    $form_state['redirect'] = 'admin/burn/bundle';
}