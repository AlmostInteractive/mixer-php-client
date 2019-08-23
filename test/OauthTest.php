<?php

use PHPUnit\Framework\TestCase;
use MixerClient\MixerGuzzleClient;
use MixerClient\MixerClient;

class OauthTest extends TestCase
{
    public function testCanCreateClassWithMinimumOptions()
    {
        $mixerGuzzleClient = new MixerGuzzleClient('CLIENT-ID');
        $mixerClient = new MixerClient($mixerGuzzleClient, 'CLIENT-ID', 'CLIENT-SECRET');
        $this->assertInstanceOf(MixerClient::class, $mixerClient);

        return $mixerClient;
    }
}
