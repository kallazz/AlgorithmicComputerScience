/*jslint browser, devel*/
/*global Image*/

const imageSources = [
    "img/gallery1.jpg",
    "img/gallery2.jpg",
    "img/gallery3.jpg",
    "img/gallery4.jpg",
    "img/gallery5.jpg",
    "img/gallery6.jpg",
    "img/gallery7.jpg",
    "img/gallery8.jpg"
];

function loadImage(src) {
    return new Promise(function (resolve, reject) {
        const img = new Image();
        img.src = src;
        img.onload = function () {
            resolve(img);
        };
        img.onerror = function () {
            reject(new Error("Nie udało się załadować obrazka: " + src));
        };
    });
}

function loadAllImages() {
    const galleryGrid = document.getElementById("gallery-grid");

    imageSources.forEach(function (src) {
        loadImage(src).then(function (img) {
            img.classList.add("gallery-image");
            galleryGrid.appendChild(img);
        }).catch(function (error) {
            console.error(error);
        });
    });
}

document.addEventListener("DOMContentLoaded", loadAllImages);
