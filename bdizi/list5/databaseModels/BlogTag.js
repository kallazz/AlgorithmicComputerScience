import database from "../database.js";

export async function getBlogTagById(id) {
    const [result] = await database.execute(
        "SELECT * FROM blogs_tags WHERE id = ?",
        [id]
    );
    const blogTag = result[0];
    return blogTag;
};

export async function getAllBlogTagIdsByBlogId(blogId) {
    const [blogsTags] = await database.execute(
        "SELECT tag_id FROM blogs_tags WHERE blog_id = ?",
        [blogId]
    );
    return blogsTags;
};

export async function createBlogTag(tagId, blogId) {
    const [result] = await database.execute(
        `INSERT INTO
        blogs_tags(tag_id, blog_id)
        VALUES (?, ?)
        `,
        [tagId, blogId]
    );

    const insertId = result.insertId;
    const newUserInfo = await getBlogTagById(insertId);
    return newUserInfo;
};