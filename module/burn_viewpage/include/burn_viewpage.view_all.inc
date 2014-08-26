<?php

function burn_user_viewpage_viewall()
{
    global $language;
    $users = BurnQueryUser::QueryAllByPager();
    $entities = BurnQueryUser::Load(array_keys($users));
    if(isset($entities)){
        $content = array();
        $result = BurnQueryUser::QueryAll();
        $entities = entity_load('burn_user', array_keys($result));
        $content = entity_metadata_view_single($entities, "view_page_teaser", $language->language, 'burn_user');
    }
    $build = array(
        'content' => $content,
        'pager' => array(
            '#markup' => theme('pager'),
            '#weight' => 10
        )
    );
    return $build;
}