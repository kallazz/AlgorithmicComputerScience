import { createBlog, getAllBlogsDesc, getBlogById, deleteBlog } from "../databaseModels/Blog.js";
import { getCommentsByBlogIdDesc, createComment } from "../databaseModels/Comment.js";
import { getUserById } from "../databaseModels/User.js";
import { getAllTags, getTagNameById } from "../databaseModels/Tag.js";
import { createBlogTag, getAllBlogTagIdsByBlogId } from "../databaseModels/BlogTag.js";

export const add_blog_get = async (req, res) => {
    const tags = await getAllTags();
    res.render("add-blog", { tags });
};

export const add_blog_post = async (req, res) => {
    const userId = res.locals.user.id;
    const { blogTitle, blogBody, tags } = req.body;
    console.log(req.body);

    try {
        const newBlog = await createBlog(userId, blogTitle, blogBody);
        console.log(`New blog added(id = ${newBlog.id})`);
        if (tags) {
            for (const tagId of tags) {
                await createBlogTag(tagId, newBlog.id);
            }
        }
        console.log(`Tags for blog(id = ${newBlog.id}) added`);
        res.status(201).redirect("/");
    }
    catch(err) {
        console.log(err);
        res.status(400).json({ errorMsg: "Couldn't create the blog" });
    }
};

export const blogs_get = async (req, res) => {
    const blogs = await getAllBlogsDesc();
    for (const blog of blogs) {
        const tagNames = [];
        let tagsIds = await getAllBlogTagIdsByBlogId(blog.id);
        for (const tagId of tagsIds) {
            const { tag_name } = await getTagNameById(tagId.tag_id);
            tagNames.push(tag_name);
        }
        blog.tags = tagNames;
    }
    res.render("blogs", { blogs });
};

export const blogs_id_get = async (req, res) => {
    const blogId = req.params.id;
    const blog = await getBlogById(blogId);
    const blogAuthor = (await getUserById(blog.user_id)).username;
    blog.author = blogAuthor;
    const comments = await getCommentsByBlogIdDesc(blogId);
    for (const comment of comments) {
        const commentAuthor = (await getUserById(comment.user_id)).username;
        comment.author = commentAuthor;
    }
    res.render("blog-detail", { blog, comments });
};

export const blogs_id_post = async (req, res) => {
    const userId = res.locals.user.id;
    const blogId = req.params.id;
    const { body } = req.body;
    await createComment(blogId, userId, body);
    console.log("Comment created")
    res.status(201).json({ successMsg: "Comment created" });
};

export const blogs_id_delete_post = async (req, res) => {
    const userId = res.locals.user.id;
    const blogId = req.params.id;
    const blog = await getBlogById(blogId);
    const blogAuthorId = blog.user_id;
    if (userId == blogAuthorId) {
        await deleteBlog(blogId);
    }
    res.redirect("/");
};
