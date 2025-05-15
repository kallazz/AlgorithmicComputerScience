/*jslint browser*/

document.documentElement.classList.add("js");

document.addEventListener("DOMContentLoaded", function () {
    const menuToggle = document.getElementById("menu-toggle");
    const navMenu = document.querySelector(".nav-menu");

    if (menuToggle) {
        menuToggle.addEventListener("click", function () {
            navMenu.classList.toggle("open");
        });
    }
});
