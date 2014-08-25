<?php

/**
 * Class Burn
 *
 * add classe to extends for entity
 */
class BurnUser extends Entity
{
    protected function defaultUri()
    {
        return array('path' => 'burn/' . $this->identifier());
    }
}

/**
 * Class BurnController
 *
 * add class to extends to EntityAPIController entityapi
 */
class BurnController extends EntityAPIController
{
    /**
     * Override the save method.
     */
    public function save($entity, DatabaseTransaction $transaction = NULL)
    {
        if (isset($entity->is_new)) {
            $entity->created = REQUEST_TIME;
        }
        $entity->changed = REQUEST_TIME;
        return parent::save($entity, $transaction);
    }
}

