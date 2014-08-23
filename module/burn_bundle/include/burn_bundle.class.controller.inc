<?php

class BurnBundleQuery {
    public static function QueryAll(){
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user_bundle');
        $result = $query->execute();
        return isset($result['burn_user_bundle']) ? $result['burn_user_bundle'] : FALSE;
    }
    public static function Load($bid){
        return entity_load('burn_user_bundle',(array) $bid);
    }
    public static function Create(){
        return entity_create('burn_user_bundle',array());
    }
    public static function Save($bundle){
        return entity_save('burn_user_bundle',$bundle);

    }
}