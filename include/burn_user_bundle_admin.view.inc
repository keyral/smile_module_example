<?php


function burn_user_bundle_admin($bundle = NULL)
{
    $render = array();
    if (isset($bundle)) {
        $bundle = new stdClass();
        $bundle->name = 'lol';
        $bundle->id = '1';
        $render[] = drupal_get_form('burn_user_bundle_form', $bundle);
        $render[] = array(
            '#type' => 'item',
            '#markup' => l(t('Return to back'), 'admin/burn/bundle'),
        );
    } else {
        $render['vertical'] = array(
            '#type' => 'vertical_tabs',
        );
        $render['vertical']['add'] = array(
            '#type' => 'fieldset',
            '#title' => t('Add bundle'),
            '#collapsible' => TRUE,
            '#group' => 'vertical_tabs',
        );
        $render['vertical']['add']['form'] = drupal_get_form('burn_user_bundle_form');
        $render['vertical']['looks'] = array(
            '#type' => 'fieldset',
            '#title' => t('Looks bundles'),
            '#collapsible' => TRUE,
            '#group' => 'vertical_tabs',
        );

        $render['vertical']['looks']['title'] = array(
            '#type' => 'item',
            '#title' => t('All bundles'),
        );
        $bundles = BurnQueryUserBundle::QueryAll();
            if (isset($bundles)) {
                //var_dump($bundles; die('lol');
            }

    }

    return $render;
}

function burn_user_bundle_title($bundle = NULL)
{
    if (isset($bundle) && $bundle != '') {
        return t("Configuration bundle to @name", array('@name' => $bundle));
    } else {
        return t("Configuration bundle");
    }
}


function burn_user_bundle_form($form, $form_state, $bundle = NULL)
{
    $form = array();
    $form['bundleid'] = array(
        '#type' => 'hidden',
        '#value' => isset($bundle->id) ? $bundle->id : '',
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

function burn_user_bundle_form_submit($form, &$form_state){
    if(isset($form_state['values']['bundleid']) && $form_state['values']['bundleid'] != ''){
    $bundle = BurnQueryUserBundle::Load($form_state['values']['bundleid']);
    }
    else {
       $bundle =  entity_create('burn_user_bundle', array());
    }
    //$bundle->name->set($form_state['values']['name']);
    $wrapper = entity_metadata_wrapper('burn_user_bundle',$bundle);
    var_dump($wrapper->getPropertyInfo());
    die('lol');

}