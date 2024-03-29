function getQueryParameters() {
    var params = {};
    window.location.search.substr(1).split('&').forEach(function (p) {
        var param = p.split('=');
        params[param[0]] = decodeURIComponent(param[1]);
    });
    return params;
}

function getBackendUrl(params) {
    var defaultHost = window.location.hostname;
    var defaultPort = '9042';
    var apiEndpoint = 'http://' + defaultHost + ':' + defaultPort + '/';
    var backendParam = params['backend'] || null;
    if (backendParam) {
        if (/^[0-9]+$/.test(backendParam)) {
            apiEndpoint = 'http://' + defaultHost + ':' + backendParam + '/';
        } else if (!backendParam.includes(':')) {
            apiEndpoint = 'http://' + backendParam + ':' + defaultPort + '/';
        } else if (!backendParam.startsWith('http:')) {
            apiEndpoint = 'http://' + backendParam;
            if (!apiEndpoint.endsWith('/')) {
                apiEndpoint += '/';
            }
        } else {
            apiEndpoint = backendParam;
        }
    }
    return apiEndpoint;
}

var params = getQueryParameters();
var backend = getBackendUrl(params);

var map = L.map('map', {
    contextmenu: true,
    contextmenuWidth: 200,
    contextmenuItems: [{
        text: 'Start',
        callback: setRoutingStart
    }, {
        text: 'Ziel',
        callback: setRoutingDest
    }, {
        text: 'Routing-Anfrage löschen',
        callback: clearRoutingRequest
    }, {
        separator: true
    }, {
        text: 'Karte hier zentrieren',
        callback: function (e) {
            map.panTo(e.latlng);
        }
    }, {
        text: 'Karte hier einzoomen',
        callback: function (e) {
            map.setView(e.latlng, 20);
        }
    }, {
        text: 'Koordinaten hier anzeigen',
        callback: function (e) {
            window.prompt('Koordinaten:',
                e.latlng.lat.toFixed(6) + ';' + e.latlng.lng.toFixed(6));
        }
    }, {
        separator: true
    }, {
        text: 'Routing-Graph laden',
        callback: requestGeoJSONOverlay
    }
    ]
});
map.setView([49.8728, 8.6512], 14);

L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors',
    maxZoom: 22,
    maxNativeZoom: 19
}).addTo(map);

L.control.scale({
    maxWidth: 240,
    metric: true,
    imperial: false,
    position: 'bottomleft'
}).addTo(map);

L.control.polylineMeasure({showMeasurementsClearControl: true}).addTo(map);

var footRouting = L.Routing.footRouting({
    serviceUrl: backend
});

var routingControl = L.Routing.control({
    waypoints: [
        // L.latLng(49.8775462288535, 8.656797409057619),
        // L.latLng(49.87023075540512, 8.651347160339357)
    ],
    language: 'de',
    router: footRouting,
    plan: L.Routing.plan([], {
        geocoder: L.Control.Geocoder.latLng({
            next: L.Control.Geocoder.nominatim({
                serviceUrl: 'https://nominatim.openstreetmap.org/'
            }),
        }),
        waypointNameFallback: function(latLng) {
            var lat = (Math.round(Math.abs(latLng.lat) * 1000000) / 1000000).toString(),
                lng = (Math.round(Math.abs(latLng.lng) * 1000000) / 1000000).toString();
            return  lat + ', ' +  lng;
        },
        maxGeocoderTolerance: 50
    }),
    routeWhileDragging: true,
    routeDragInterval: 50,
    reverseWaypoints: true,
    showAlternatives: true,
    lineOptions: {
        styles: [
            {color: 'black', opacity: 0.15, weight: 9},
            {color: 'white', opacity: 0.8, weight: 6},
            {color: 'red', opacity: 1, weight: 2}
        ]
    },
    altLineOptions: {
        styles: [
            {color: 'black', opacity: 0.15, weight: 9},
            {color: 'white', opacity: 0.8, weight: 6},
            {color: 'blue', opacity: 0.5, weight: 2}
        ]
    },
    collapsible: true
}).addTo(map);

L.Routing.errorControl(routingControl).addTo(map);

var geoJSONOverlay = L.control.geoJSONOverlay({backend: backend}).addTo(map);

L.control.mapLinks().addTo(map);

function setRoutingStart(e) {
    routingControl.spliceWaypoints(0, 1, e.latlng);
}

function setRoutingDest(e) {
    routingControl.spliceWaypoints(
        routingControl.getWaypoints().length - 1, 1, e.latlng);
}

function clearRoutingRequest(e) {
    routingControl.setWaypoints([]);
}

function requestGeoJSONOverlay(e) {
    geoJSONOverlay._requestData();
}

function updateUrlHash() {
    var center = map.getCenter();
    var hash = '#' + center.lat + ';' + center.lng + ';' + map.getZoom();
    history.replaceState({}, '', hash);
}

function handleUrlHash() {
    var hash = window.location.hash.substring(1);
    var values = hash.split(';').map(function (s) {
        return parseFloat(s)
    });
    if (values.length >= 2) {
        var lat = values[0];
        var lng = values[1];
        var zoom = values[2];
        map.setView(L.latLng(lat, lng), zoom);
        //geoJSONOverlay._setAutoRefresh(true);
    }
}

map.on({moveend: updateUrlHash, zoomend: updateUrlHash});
window.addEventListener('hashchange', handleUrlHash);
window.addEventListener('load', handleUrlHash);

window.addEventListener('load', function () {
    var container = document.querySelector('.leaflet-routing-geocoders');

    var profileSelectorContainer = L.DomUtil.create('div', 'profile-selector', container);

    var select = L.DomUtil.create('select', '', profileSelectorContainer);
    for (var p of searchProfiles) {
        var opt = document.createElement('option');
        opt.innerText = p.name;
        select.appendChild(opt);
    }
    var customOpt = document.createElement('option');
    customOpt.innerText = 'Benutzerdefiniert';
    select.appendChild(customOpt);

    L.DomEvent.on(select, 'change', function (e) {
        var profile = searchProfiles.find(p => p.name === e.target.value);
        if (profile) {
            footRouting.options.searchProfile = profile.profile;
            routingControl.route();
        }
    });

    var profileBtn =
        L.DomUtil.create('button', 'leaflet-routing-profile-btn', profileSelectorContainer);
    profileBtn.setAttribute('type', 'button');
    profileBtn.innerText = 'Suchprofil bearbeiten';

    var profileEditor = L.DomUtil.get('search-profile-editor');
    var profileTextarea = L.DomUtil.get('search-profile-text');
    var profileSaveButton = L.DomUtil.get('search-profile-save');
    L.DomEvent.on(profileBtn, 'click', function () {
        profileTextarea.value =
            JSON.stringify(footRouting.options.searchProfile, null, 2);
        L.DomUtil.addClass(profileEditor, 'visible');
    });
    L.DomEvent.on(profileSaveButton, 'click', function () {
        L.DomUtil.removeClass(profileEditor, 'visible');
        footRouting.options.searchProfile = JSON.parse(profileTextarea.value);
        customOpt.selected = true;
        routingControl.route();
    });
    L.DomEvent.disableClickPropagation(profileEditor);
    L.DomEvent.on(profileEditor, 'mousewheel', function (e) {
        L.DomEvent.stopPropagation(e);
    });
});
