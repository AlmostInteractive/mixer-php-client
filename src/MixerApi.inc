<?php

declare(strict_types=1);

namespace MixerApi;

use GuzzleHttp\Client;
use MixerApi\Auth\OauthApi;


class MixerApi
{
    private $oauthApi;

    public function __construct(Client $mixerGuzzleClient, string $clientId, string $clientSecret, Client $authGuzzleClient = null) {
        $this->oauthApi = new OauthApi($clientId, $clientSecret, $authGuzzleClient);
    }

    public function getOauthApi(): OauthApi
    {
        return $this->oauthApi;
    }
}
