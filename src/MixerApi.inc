<?php

declare(strict_types=1);

namespace MixerApi;

use GuzzleHttp\Client;
use MixerApi\Auth\OauthApi;

class MixerApi
{
    private $oauthApi;

    public function __construct(string $clientId, string $clientSecret, Client $apiGuzzleClient = null) {
        $apiGuzzleClient = $apiGuzzleClient ?? new MixerGuzzleClient($clientId);

        $this->oauthApi = new OauthApi($clientId, $clientSecret, $apiGuzzleClient);
    }

    public function getOauthApi(): OauthApi
    {
        return $this->oauthApi;
    }
}
