import matplotlib.pyplot as plt

Centre_dot = plt.Circle((0.3,0.3),0.01, color = 'red')
circle1 = plt.Circle((0.3, 0.3), 0.1, color='r',fill=False)
circle2 = plt.Circle((0.3, 0.3), 0.2, color='blue',fill=False)
circle3 = plt.Circle((0.3, 0.3), 0.3, color='g',fill=False, clip_on=False)
circle4 = plt.CirclePolygon((0.3,0.3), radius=5,  resolution=20)

fig, ax = plt.subplots()

ax.add_patch(Centre_dot)
ax.add_patch(circle1)
ax.add_patch(circle2)
ax.add_patch(circle3)
ax.add_patch(circle4)
plt.show()
fig.savefig('plotcircles.png')
