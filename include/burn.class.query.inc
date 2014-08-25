<?php
class BurnWrapperUser extends EntityDrupalWrapper {
    public function __construct($data = NULL, $info = array()) {
        parent::__construct('burn_user', $data, $info);
    }

}
class BurnQueryUser
{
    static function QueryAll()
    {
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user');
        $result = $query->execute();
        return isset($result['burn_user']) ? $result['burn_user'] : FALSE;
    }
    static function QueryByType($type = NULL){
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'burn_user');
        $query->entityCondition('bundle', $type);
        $result = $query->execute();
        return isset($result['burn_user']) ? $result['burn_user'] : FALSE;
    }
    static function Load($bids = array(), $conditions = array(), $reset = FALSE)
    {
        return entity_load('burn_user', $bids, $conditions, $reset);
    }

    static function Save($user)
    {
        return entity_save('burn_user', $user);
    }
    static function Delete($id){
        return entity_delete('burn_user', $id);
    }
}