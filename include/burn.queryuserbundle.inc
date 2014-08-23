<?php


class BurnQueryUserBundle {

    static function QueryAll(){
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user_bundle');
        $result = $query->execute();
        return isset($result['burn_user_bundle']) ? $result['burn_user_bundle'] : FALSE;
    }


}