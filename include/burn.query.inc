<?php


class BurnQuery {

    static function QueryAll(){
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user');
        $result = $query->execute();
        if(isset($result['burn_user'])){
            return $result['burn_user'];
        }
        else {
            return false;
        }
    }

    static function QueryByType($type = NULL){
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user');
        $query->entityCondition('bundle', $type);
        $result =  $query->execute();
        if(isset($result['burn_user'])){
            return $result['burn_user'];
        }
        else {
            return false;
        }
    }

    static function Load($bids = array(), $conditions = array(), $reset = FALSE){
       return entity_load('burn_user',$bids, $conditions, $reset );
    }


}