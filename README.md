# mixer-php-client

A PHP 7.1 library for interfacing with the Mixer.com API.

## Installation

`composer require almostinteractive/mixer-php-client`

## Usage Example

```php
$mixerGuzzleClient = new MixerGuzzleClient('MY_CLIENT_ID');
$apiClient = new MixerApi('MY_CLIENT_ID', 'MY_CLIENT_SECRET', $mixerGuzzleClient);


$scope = [
    'channel:analytics:self',
    'channel:details:self',
    'user:details:self'
];
$scope = implode('%20', $scope);
$authUrl = $apiClient->getOauthApi()->getAuthUrl('http://localhost/callback.php', 'code', $scope, true, null);


$response = $apiClient->getOauthApi()->getUserAccessToken($code, 'http://localhost/callback.php');
$token = json_decode($response->getBody()->getContents(), true);
$accessToken = $token['access_token'];
$refreshToken = $token['refresh_token'];

$response = $apiClient->getUsersApi()->getUserByAccessToken($accessToken);
$userData = json_decode($response->getBody()->getContents(), true);
```

## Notes from the Author
I plan on only adding the endpoints as I need them. Pull requests welcome. Requests will be duly considered.
