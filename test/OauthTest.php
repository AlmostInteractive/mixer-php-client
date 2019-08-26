<?php

use PHPUnit\Framework\TestCase;
use MixerApi\MixerGuzzleClient;
use MixerApi\MixerApi;

class OauthTest extends TestCase
{
    public function testCanCreateClassWithMinimumOptions()
    {
        $mixerGuzzleClient = new MixerGuzzleClient('CLIENT-ID');
        $mixerApi = new MixerApi('CLIENT-ID', 'CLIENT-SECRET', $mixerGuzzleClient);
        $this->assertInstanceOf(MixerApi::class, $mixerApi);

        return $mixerApi;
    }
}
