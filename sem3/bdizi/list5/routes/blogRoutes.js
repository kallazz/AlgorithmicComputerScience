import Router from "express";
import { requireAuth } from "../middleware/authMiddleware.js";
import {
    add_blog_get,
    add_blog_post,
    blogs_get,
    blogs_id_get,
    blogs_id_post,
    blogs_id_delete_post } from "../controllers/blogsController.js";

const router = Router();

router.get("/add-blog", requireAuth, add_blog_get);
router.post("/add-blog", requireAuth, add_blog_post);
router.get("/blogs", requireAuth, blogs_get);
router.get("/blogs/:id", requireAuth, blogs_id_get);
router.post("/blogs/:id", requireAuth, blogs_id_post);
router.post("/blogs/:id/delete", requireAuth, blogs_id_delete_post);

export default router;