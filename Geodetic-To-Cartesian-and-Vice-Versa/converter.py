import pyproj
#ECEF，earth centered eath fixed
#该坐标系以地球质心为原点，Z轴向北沿地球自转轴方向，X轴指向经纬度的（0，0）位置，右手系Y轴指向90度经线。该系与地球一同转动。
#我们为了让xyz更小，则可以确定一个原点的经纬度，然后可以得到ECEF坐标系下的一个坐标(x,y,z)，然后后面所有经纬度转换得到的ECEF坐标都减去基准的(x,y,z),然后xyz要转换为经纬度之前先3加上这个基准的(x,y,z),

# Definition of the function to convert Cartesian coordinates to Geodetic
def cartesian_to_geodetic(x, y, z):
    ecef = pyproj.Proj(proj='geocent', ellps='WGS84', datum='WGS84')
    lla = pyproj.Proj(proj='latlong', ellps='WGS84', datum='WGS84')

    lon, lat, alt = pyproj.transform(ecef, lla, x, y, z, radians=False)

    print("\n")
    print ("Latitude: %f" % lat)
    print ("Longitude: %f" % lon)
    print ("Height in metres: %f" % alt)


# Definition of the function to convert Geodetic coordinates to Cartesian
def geodetic_to_cartesian(lat, lon, alt):
    ecef = pyproj.Proj(proj='geocent', ellps='WGS84', datum='WGS84')
    lla = pyproj.Proj(proj='latlong', ellps='WGS84', datum='WGS84')

    x, y, z = pyproj.transform(lla, ecef, lon, lat, alt, radians=False)

    print("\n")
    print ("X: %f" % x)
    print ("Y: %f" % y)
    print ("Z: %f" % z)
    
    
geodetic_to_cartesian(31, 121, 3)
cartesian_to_geodetic(-2818285.117100, 4690414.095804, 3265895.061768)

'''
# Brings up a prompt, basically just to make it easier for the user to enter the values
choice = input("Enter A (Cartesian to Geodetic) or B (Geodetic to Cartesian)" + "\r\n")

# Self explanatory
if choice == 'A':
    print("You chose Cartesian to Geodetic." + "\r\n")
    print("Enter these values: " + "\n")
    x = input("Enter X coordinate:  ")
    y = input("Enter Y coordinate:  ")
    z = input("Enter Z coordinate:  ")
    cartesian_to_geodetic(x, y, z)

# Self Explanatory too
elif choice == 'B':
    print("You chose Geodetic to Cartesian." + "\r\n")
    print("Enter these values: " + "\n")
    lat = input("Enter Latitude:  ")
    lon = input("Enter Longitude:  ")
    alt = input("Enter Height in metres:  ")
    geodetic_to_cartesian(lat, lon, alt)

# Unless someone is trying to play chess or something else other than do their homework ...lol
else:
    print("Sorry wrong selection...")
    exit
'''
