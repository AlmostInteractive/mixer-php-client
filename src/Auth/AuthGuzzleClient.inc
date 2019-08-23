<?php

declare(strict_types=1);

namespace MixerApi\Auth;

use GuzzleHttp\Client;

class AuthGuzzleClient extends Client
{
    private const BASE_URI = 'https://mixer.com/api/v1/oauth/token/';

    public function __construct(array $config = [])
    {
        parent::__construct($config + [
                'base_uri' => self::BASE_URI
            ]);
    }
}
