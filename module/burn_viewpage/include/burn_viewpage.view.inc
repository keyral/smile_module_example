<?php

function burn_user_viewpage_view($user){
    global $language;
    return burn_user_view($user, 'view_page',$language->language);
}