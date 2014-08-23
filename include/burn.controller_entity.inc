<?php

class Burn extends Entity
{
    protected function defaultUri()
    {
        return array('path' => 'lawmakers/' . $this->identifier());
    }
}
