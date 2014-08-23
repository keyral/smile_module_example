<?php

/**
 * Class Burn
 *
 * add classe to extends for entity
 */
class Burn extends Entity
{
    protected function defaultUri()
    {
        return array('path' => 'burn/' . $this->identifier());
    }
}
