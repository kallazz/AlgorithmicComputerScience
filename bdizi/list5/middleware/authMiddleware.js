import jwt from "jsonwebtoken";
import dotenv from "dotenv";
dotenv.config();
import { getUserById } from "../databaseModels/User.js";

export const requireAuth = (req, res, next) => {
    const token = req.cookies.jwt;

    if (token) {
        jwt.verify(token, process.env.JWT_SECRET_KEY, (err, decodedToken) => {
            if (err) {
                console.log(err);
                res.redirect("/login");
            }
            next();
        });
    } else {
        res.redirect("/login");
    }
};

export const checkUser = (req, res, next) => {
    const token = req.cookies.jwt;
    res.locals.user = null;
    if (token) {
        jwt.verify(token, process.env.JWT_SECRET_KEY, async (err, decodedToken) => {
            if (err) {
                console.log(err);
                next();
            } else {
                const user = await getUserById(decodedToken.id);
                res.locals.user = user;
                next();
            }
        })
    }
    else {
        next();
    }
};
