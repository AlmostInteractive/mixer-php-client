<?php

declare(strict_types=1);

namespace MixerClient;

use GuzzleHttp\Client;
use MixerClient\Auth\OauthApi;


class MixerClient
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
