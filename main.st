Object subclass: #Ride
    instanceVariableNames: 'rideID pickupLocation dropoffLocation distance'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.

Ride>>initializeWithID: anID pickup: aPickup dropoff: aDropoff distance: aDistance
    rideID := anID.
    pickupLocation := aPickup.
    dropoffLocation := aDropoff.
    distance := aDistance.
    ^ self.

Ride>>fare
    ^ distance * 1.0.

Ride>>rideDetails
    Transcript
        show: 'Ride ID: ', rideID printString, 
             ' | Pickup: ', pickupLocation,
             ' | Dropoff: ', dropoffLocation,
             ' | Distance: ', distance printString,
             ' | Fare: ', (self fare) printString;
        cr.

Ride subclass: #StandardRide
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.

StandardRide>>fare
    ^ distance * 1.2.

Ride subclass: #PremiumRide
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.

PremiumRide>>fare
    ^ distance * 2.0.

Object subclass: #Driver
    instanceVariableNames: 'driverID name rating assignedRides'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.

Driver>>initialize
    assignedRides := OrderedCollection new.
    ^ self.

Driver>>initializeWithID: anID name: aName rating: aRating
    driverID := anID.
    name := aName.
    rating := aRating.
    self initialize.
    ^ self.

Driver>>addRide: aRide
    assignedRides add: aRide.

Driver>>getDriverInfo
    Transcript
        show: 'Driver ID: ', driverID printString,
             ' | Name: ', name,
             ' | Rating: ', rating printString,
             ' | Completed Rides: ', assignedRides size printString;
        cr.

Object subclass: #Rider
    instanceVariableNames: 'riderID name requestedRides'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.

Rider>>initialize
    requestedRides := OrderedCollection new.
    ^ self.

Rider>>initializeWithID: anID name: aName
    riderID := anID.
    name := aName.
    self initialize.
    ^ self.

Rider>>requestRide: aRide
    requestedRides add: aRide.

Rider>>viewRides
    Transcript 
        show: 'Rider ', name, ' Ride History:', cr.
    requestedRides do: [:ride | ride rideDetails].

| ride1 ride2 driver rider rideList |

ride1 := StandardRide new initializeWithID: 001 pickup: '410 Meijer Drive, Florence, KY' dropoff: '2939 Terminal Drive, Hebron, KY' distance: 10.
ride2 := PremiumRide new initializeWithID: 002 pickup: '6178 College Station Drive, Williamsburg, KY' dropoff: '994 Aviation Boulevard, Williamsburg KY' distance: 25.

rideList := OrderedCollection with: ride1 with: ride2.
rideList do: [:ride | ride rideDetails].

driver := Driver new initializeWithID: 1 name: 'Nicolas' rating: 4.9.
driver addRide: ride1.
driver addRide: ride2.
driver getDriverInfo.

rider := Rider new initializeWithID: 1001 name: 'Dax'.
rider requestRide: ride1.
rider requestRide: ride2.
rider viewRides.
